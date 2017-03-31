#include "gamestateplaying.hpp"

#include <string>
#include <fstream>
#include <sstream>

#include "allegro5/allegro_image.h"

#include "bitmapservice.hpp"

#include "actordrawer.hpp"

GameStatePlaying::GameStatePlaying(Game* game) : GameStateBase(game)
{

}

void GameStatePlaying::Enter()
{

}

void GameStatePlaying::Exit()
{
    delete this->game->current_map;
    this->game->current_map = nullptr;
}

void GameStatePlaying::Tick()
{

}

void GameStatePlaying::Render()
{
    // Game render logic
    Map* current_map = this->game->current_map;

    if (current_map)
    {



    Vector2 current_pos = this->game->current_character->GetPosition();

    // Draw map
    Vector2 tile_step_x = Vector2(64, 32)/2;
    Vector2 tile_step_y = Vector2(-64, 32)/2;

    Vector2 base_draw = Vector2((640 - 64)/2, (480 - 32)/2);

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
                    ALLEGRO_BITMAP* tile_bitmap = BitmapService::Instance()->GetBitmap(bitmap_name);

                    Vector2 draw_pos = base_draw + (tile_step_x * x) + (tile_step_y * y);

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
    Character* mychar = this->game->current_character;

    Vector2 middle = Vector2(640/2, 480/2);

    std::list<Actor*> actor_list = this->game->current_map->GetActorList();
    for (std::list<Actor*>::iterator iter = actor_list.begin(); iter != actor_list.end(); ++iter)
    {
        Actor* actor = *iter;
        if (actor != self_actor)
        {
            Vector2 pos_offset = mychar->GetPosition() - actor->GetPosition();
            Vector2 tile_mid = middle + (tile_step_x * pos_offset.x) + (tile_step_y * pos_offset.y);
            actordrawer.DrawActorOnTile(actor, tile_mid);
        }
    }

    // Draw own character
    actordrawer.DrawActorOnTile(mychar, middle);



    }

    // Screen drawing
    this->game->DrawScreens();

}

void GameStatePlaying::HandlePacket(PacketBase* packet)
{
    if (packet->GetType() == PacketBase::PACKET_CHARACTER_POSITION)
    {
        PacketCharacterPosition* char_pos = static_cast<PacketCharacterPosition*>(packet);

        if (char_pos->GetCharacterId() == this->game->current_character->GetCharacterId())
        {
            Character* character = this->game->current_character;
            Map* cur_map = this->game->current_map;

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
        else if (this->game->current_map->GetMapId() == char_pos->GetMapId())
        {
            std::list<Actor*> actor_list = this->game->current_map->GetActorList();
            std::list<Actor*>::iterator iter;
            for (iter = actor_list.begin(); iter != actor_list.end(); ++iter)
            {
                Actor* actor = *iter;
                if (actor->IsPlayer())
                {
                    Character* character = static_cast<Character*>(actor);
                    if (character->GetCharacterId() == char_pos->GetCharacterId())
                    {
                        std::cout << "Got position update for character with id: " << char_pos->GetCharacterId() << std::endl;
                    }
                }
            }
        }
    }
}

void GameStatePlaying::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{
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
    else if (keyboard.keycode == ALLEGRO_KEY_SPACE)
    {
        this->game->current_character->SetHasNowall(!this->game->current_character->GetHasNowall());
        return;
    }
    else
    {
        return;
    }

    Character* cur_char = this->game->current_character;
    cur_char->SetDirection(dir);
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

        //std::cout << "Moved to: " << targ_pos.x << "/" << targ_pos.y << std::endl;
    }
    catch (...)
    {
        //std::cout << "Could not move to: " << targ_pos.x << "/" << targ_pos.y << std::endl;
    }
}

void GameStatePlaying::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStatePlaying::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    if (true) return;

    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStatePlaying::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    if (true) return;

    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStatePlaying::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    if (true) return;

    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
