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
    this->game->current_map = new Map();
    this->game->current_map->LoadMap(1);

    this->game->current_character = new Character();
    this->game->current_character->Warp(this->game->current_map, Vector2(10, 10));
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
    Vector2 current_pos = this->game->current_character->GetPosition();
    Map* current_map = this->game->current_map;

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
            DrawSpecs specs = actordrawer.GetDrawSpecs(actor);
            Vector2 pos_offset = mychar->GetPosition() - actor->GetPosition();
            Vector2 tile_mid = middle + (tile_step_x * pos_offset.x) + (tile_step_y * pos_offset.y);
            Vector2 draw_pos = tile_mid - Vector2(specs.sprite_size.x/2, specs.sprite_size.y);
            al_draw_tinted_bitmap_region(specs.bitmap, specs.tint,
                                         specs.sprite_start.x, specs.sprite_start.y,
                                         specs.sprite_size.x, specs.sprite_size.y,
                                         draw_pos.x, draw_pos.y, specs.draw_flags);
        }
    }

    // Draw own character
    DrawSpecs specs = actordrawer.GetDrawSpecs(mychar);
    Vector2 draw_pos = middle - Vector2(specs.sprite_size.x/2, specs.sprite_size.y);
    al_draw_tinted_bitmap_region(specs.bitmap, specs.tint,
                                 specs.sprite_start.x, specs.sprite_start.y,
                                 specs.sprite_size.x, specs.sprite_size.y,
                                 draw_pos.x, draw_pos.y, specs.draw_flags);

    // Screen drawing
    this->game->DrawScreens();

}

void GameStatePlaying::HandlePacket(PacketBase* packet)
{

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
    Vector2 targ_pos = cur_char->GetPosition() + adder;
    try
    {
        cur_char->Move(targ_pos);
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
