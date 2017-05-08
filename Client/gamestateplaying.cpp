#include "gamestateplaying.hpp"

#include <string>
#include <fstream>
#include <sstream>

#include "allegro5/allegro_image.h"

#include "bitmapservice.hpp"

#include "actordrawer.hpp"

#include "gamestatecharacterview.hpp"
#include "screenmaker.hpp"

GameStatePlaying::GameStatePlaying(Game* game) : GameStateBase(game)
{

}

void GameStatePlaying::Enter()
{
    this->game->current_character->ChangeState(new ActorStateStand(this->game->current_character));
}

void GameStatePlaying::Exit()
{
    delete this->game->current_map;
    this->game->current_map = nullptr;
}

void GameStatePlaying::Tick()
{
    Map* cur_map = this->game->current_map;

    if (cur_map)
    {
        cur_map->Update();
    }
}

void GameStatePlaying::Render()
{
    // Game render logic
    Map* current_map = this->game->current_map;

    if (current_map)
    {
        Character* mychar = this->game->current_character;

        Vector2 base_draw = Vector2((640 - 64)/2, (480 - 32)/2);
        Vector2 tile_step_x = Vector2(64, 32)/2;
        Vector2 tile_step_y = Vector2(-64, 32)/2;

        Vector2 draw_offset;
        if (mychar->IsMoving())
        {
            double percent = 1.0 - mychar->GetStatePercentDone();
            Vector2 dir = mychar->GetDirectionVector();
            draw_offset = ((tile_step_x * dir.x) + (tile_step_y * dir.y)) * percent;
        }


        Vector2 current_pos = this->game->current_character->GetPosition();

        const BitmapSet* tile_set = BitmapService::Instance()->GetBitmapSet(BitmapService::BITMAPSET_TILE);

        // Draw map
        int range = 14;
        for (int x = -range; x < range; x++)
        {
            for (int y = -range; y < range; y++)
            {
                Vector2 targ_coords = current_pos + Vector2(x, y);
                if (current_map->CoordsAreInBounds(targ_coords))
                {
                    MapTile& tile = current_map->GetTile(targ_coords);

                    std::stringstream ss;
                    ss << "tile_";
                    ss << tile.GetSpriteId();

                    std::string bitmap_name = ss.str();

                    try
                    {
                        //ALLEGRO_BITMAP* tile_bitmap = BitmapService::Instance()->GetBitmap(bitmap_name);
                        ALLEGRO_BITMAP* tile_bitmap = tile_set->GetBitmap(tile.GetSpriteId());

                        Vector2 draw_pos = base_draw + (tile_step_x * x) + (tile_step_y * y);
                        draw_pos = draw_pos + draw_offset;

                        al_draw_bitmap(tile_bitmap, draw_pos.x, draw_pos.y, 0);
                    }
                    catch (BitmapNotLoadedException &e)
                    {

                    }
                }
            }
        }

        // Draw actors
        ActorDrawer actordrawer;

        Actor* self_actor = this->game->current_character;

        Vector2 middle = Vector2(640/2, 480/2);

        std::list<Actor*> actor_list = this->game->current_map->GetActorList();
        for (std::list<Actor*>::iterator iter = actor_list.begin(); iter != actor_list.end(); ++iter)
        {
            Actor* actor = *iter;
            if (actor != self_actor)
            {
                Vector2 pos_offset = actor->GetPosition() - mychar->GetPosition();
                Vector2 tile_mid = middle + (tile_step_x * pos_offset.x) + (tile_step_y * pos_offset.y);

                if (actor->IsMoving())
                {
                    double percent = 1.0 - actor->GetStatePercentDone();
                    Vector2 dir = actor->GetDirectionVector();

                    Vector2 offset = ((tile_step_x * dir.x) + (tile_step_y * dir.y)) * percent;
                    tile_mid = tile_mid - offset;
                }

                actordrawer.DrawActorOnTile(actor, tile_mid + draw_offset);
            }
        }

        // Draw own character
        actordrawer.DrawActorOnTile(mychar, middle);

    }

    //update status bars
    this->game->GetCurrentScreen()->GetGuiById("health_bar")->SetSize(Vector2(112*(static_cast<float>(game->GetCurrentCharacter()->GetHealth())/game->GetCurrentCharacter()->GetMaxHealth()), 26));

    // Screen drawing
    this->game->DrawScreens();

}

void GameStatePlaying::HandlePacket(PacketBase* packet)
{
    if (packet->GetType() == PacketBase::PACKET_CHARACTER_MAP_ENTER)
    {
        PacketCharacterMapEnter* enter = static_cast<PacketCharacterMapEnter*>(packet);
        Map* cur_map = this->game->current_map;
        if (cur_map && cur_map->GetMapId() == enter->GetMapId())
        {
            bool in_map = false;

            std::list<Character*> char_list = cur_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* character = *iter;
                if (character->GetCharacterId() == enter->GetCharacterId())
                {
                    in_map = true;
                }
            }

            if (!in_map)
            {
                Character* character = new Character();
                character->SetCharacterId(enter->GetCharacterId());
                character->Warp(cur_map, Vector2(0, 0));

                PacketCharacterDataRequest* request = new PacketCharacterDataRequest();
                request->SetCharacterId(character->GetCharacterId());
                request->SetRequestAppearance(true);
                request->SetRequestPosition(true);

                this->game->SendPacket(request);
            }
        }
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_MAP_LEAVE)
    {
        PacketCharacterMapLeave* leave = static_cast<PacketCharacterMapLeave*>(packet);
        Map* cur_map = this->game->current_map;
        if (cur_map && cur_map->GetMapId() == leave->GetMapId())
        {
            Character* character = nullptr;

            std::list<Character*> char_list = cur_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* check = *iter;
                if (check->GetCharacterId() == leave->GetCharacterId())
                {
                    character = check;
                }
            }

            if (character)
            {
                cur_map->HandleActorLeave(character);
                delete character;
            }
        }
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_APPEARANCE)
    {
        PacketCharacterAppearance* return_character = static_cast<PacketCharacterAppearance*>(packet);
        Map* cur_map = this->game->current_map;
        if (cur_map)
        {
            std::list<Character*> char_list = cur_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* character = *iter;
                if (character->GetCharacterId() == return_character->GetCharacterId())
                {
                    character->SetName(return_character->GetName());
                    character->SetGender(static_cast<Character::Gender>(return_character->GetGender()));
                    character->SetSkin(static_cast<Character::Skin>(return_character->GetSkin()));
                    character->SetHair(static_cast<Character::Hair>(return_character->GetHair()));
                    character->SetHairColor(static_cast<Character::HairColor>(return_character->GetHairColor()));
                }
            }
        }
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_POSITION)
    {
        PacketCharacterPosition* char_pos = static_cast<PacketCharacterPosition*>(packet);
        Map* cur_map = this->game->current_map;
        if (char_pos->GetCharacterId() == this->game->current_character->GetCharacterId())
        {
            Character* character = this->game->current_character;

            unsigned int map_id = char_pos->GetMapId();
            Vector2 pos = Vector2(char_pos->GetPositionX(), char_pos->GetPositionY());
            Actor::Direction dir = static_cast<Actor::Direction>(char_pos->GetDirection());

            Map* targ_map = cur_map;
            bool change_map = (!cur_map) || (targ_map->GetMapId() != map_id);
            if (change_map)
            {
                targ_map = new Map();
                targ_map->LoadMap(map_id);
            }

            character->Warp(targ_map, pos);
            character->SetDirection(dir);

            if (change_map)
            {
                if (cur_map)
                {
                    cur_map->UnloadMap();
                    delete cur_map;
                }
                this->game->current_map = targ_map;
            }
        }
        else if (cur_map && cur_map->GetMapId() == char_pos->GetMapId())
        {
            std::list<Character*> char_list = this->game->current_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* character = *iter;
                if (character->GetCharacterId() == char_pos->GetCharacterId())
                {
                    Vector2 pos = Vector2(char_pos->GetPositionX(), char_pos->GetPositionY());
                    Actor::Direction dir = static_cast<Actor::Direction>(char_pos->GetDirection());

                    character->Warp(cur_map, pos);
                    character->SetDirection(dir);
                }
            }
        }
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_TURN)
    {
        PacketCharacterTurn* turn = static_cast<PacketCharacterTurn*>(packet);

        Map* cur_map = this->game->current_map;
        if (cur_map)
        {
            std::list<Character*> char_list = cur_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* c = *iter;
                if (c->GetCharacterId() == turn->GetCharacterId())
                {
                    c->Turn(static_cast<Actor::Direction>(turn->GetDirection()));
                }
            }
        }
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_WALK)
    {
        PacketCharacterWalk* walk_packet = static_cast<PacketCharacterWalk*>(packet);

        Map* cur_map = this->game->current_map;
        if (cur_map)
        {
            std::list<Character*> char_list = cur_map->GetCharacterList();
            std::list<Character*>::iterator iter;
            for (iter = char_list.begin(); iter != char_list.end(); ++iter)
            {
                Character* c = *iter;
                if (c->GetCharacterId() == walk_packet->GetCharacterId())
                {
                    c->Warp(cur_map, Vector2(walk_packet->GetFromX(), walk_packet->GetFromY()));
                    c->SetDirection(static_cast<Actor::Direction>(walk_packet->GetDirection()));
                    c->Move(Vector2(walk_packet->GetToX(), walk_packet->GetToY()));
                }
            }
        }
    }
}

void GameStatePlaying::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{
    if (keyboard.keycode == ALLEGRO_KEY_UP || keyboard.keycode == ALLEGRO_KEY_DOWN ||
        keyboard.keycode == ALLEGRO_KEY_LEFT || keyboard.keycode == ALLEGRO_KEY_RIGHT)
    {
        Character* cur_char = this->game->current_character;
        if (!cur_char->CanMove()) return;

        Vector2 adder;
        Actor::Direction dir;
        if (keyboard.keycode == ALLEGRO_KEY_UP)
        {
            adder = Vector2(0, -1);
            dir = Actor::DIR_UP;
        }
        else if (keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            adder = Vector2(0, 1);
            dir = Actor::DIR_DOWN;
        }
        else if (keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            adder = Vector2(-1, 0);
            dir = Actor::DIR_LEFT;
        }
        else if (keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            adder = Vector2(1, 0);
            dir = Actor::DIR_RIGHT;
        }


        if (cur_char->GetDirection() != dir)
        {
            cur_char->Turn(dir);

            PacketCharacterTurn* packet = new PacketCharacterTurn();
            packet->SetCharacterId(cur_char->GetCharacterId());
            packet->SetDirection(dir);

            this->game->SendPacket(packet);

            return;
        }

        Vector2 cur_pos = cur_char->GetPosition();
        Vector2 targ_pos = cur_pos + adder;
        try
        {
            cur_char->Move(targ_pos);

            PacketCharacterWalk* packet = new PacketCharacterWalk();
            packet->SetCharacterId(cur_char->GetCharacterId());
            packet->SetFromX(cur_pos.x);
            packet->SetFromY(cur_pos.y);
            packet->SetToX(targ_pos.x);
            packet->SetToY(targ_pos.y);
            packet->SetDirection(dir);

            this->game->SendPacket(packet);
        }
        catch (...)
        {

        }
    }
    else if (keyboard.keycode == ALLEGRO_KEY_SPACE)
    {
        Character* cur_char = this->game->current_character;
        cur_char->SetHasNowall(!cur_char->GetHasNowall());
    }
    else if (keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
    {
        PacketCharacterLogout* packet = new PacketCharacterLogout();
        this->game->SendPacket(packet);

        ScreenMakerCharacterView maker(this->game);
        this->game->PushScreen(maker.MakeScreen());

        this->game->current_character = nullptr;
        this->game->ChangeState(new GameStateCharacterView(this->game));
    }


}

void GameStatePlaying::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStatePlaying::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStatePlaying::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStatePlaying::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
