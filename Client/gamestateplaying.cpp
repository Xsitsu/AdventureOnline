#include "gamestateplaying.hpp"

#include <string>
#include <fstream>

#include "allegro5/allegro_image.h"

#include "bitmapservice.hpp"

GameStatePlaying::GameStatePlaying(Game* game) : GameStateBase(game)
{

}

void GameStatePlaying::Enter()
{
    this->game->current_map = new Map();
    this->game->current_map->LoadMap(1);

    this->game->current_character = new Character();
    this->game->current_character->Warp(this->game->current_map, Vector2(10, 10));


    ALLEGRO_BITMAP* tile_bitmap = al_load_bitmap("resource/image/tile.bmp");

    if (tile_bitmap)
    {
        al_convert_mask_to_alpha(tile_bitmap, al_map_rgb(0, 0, 0));
    }

    BitmapService::Instance()->RegisterBitmap("tile_1", tile_bitmap);
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

    Vector2 step_x = Vector2(64, 32)/2;
    Vector2 step_y = Vector2(-64, 32)/2;

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

                std::string bitmap_name = "tile_";
                //bitmap_name += tile.GetSpriteId();
                bitmap_name += "1";

                try
                {
                    ALLEGRO_BITMAP* tile_bitmap = BitmapService::Instance()->GetBitmap(bitmap_name);

                    Vector2 draw_pos = base_draw + (step_x * x) + (step_y * y);

                    al_draw_bitmap(tile_bitmap, draw_pos.x, draw_pos.y, 0);
                }
                catch (BitmapNotLoadedException &e)
                {

                }
            }
        }
    }

    // Draw actors
    std::list<Actor*> actor_list = this->game->current_map->GetActorList();
    for (std::list<Actor*>::iterator iter = actor_list.begin(); iter != actor_list.end(); ++iter)
    {
        Actor* actor = *iter;
    }

    // Draw own character


    // Screen drawing
    this->game->DrawScreens();

}

void GameStatePlaying::HandlePacket(PacketBase* packet)
{

}

void GameStatePlaying::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{
    Vector2 adder;
    if (keyboard.keycode == ALLEGRO_KEY_UP)
    {
        adder = Vector2(0, -1);
    }
    else if (keyboard.keycode == ALLEGRO_KEY_DOWN)
    {
        adder = Vector2(0, 1);
    }
    else if (keyboard.keycode == ALLEGRO_KEY_LEFT)
    {
        adder = Vector2(-1, 0);
    }
    else if (keyboard.keycode == ALLEGRO_KEY_RIGHT)
    {
        adder = Vector2(1, 0);
    }
    else
    {
        return;
    }

    Map* cur_map = this->game->current_map;
    Character* cur_char = this->game->current_character;

    Vector2 targ_pos = cur_char->GetPosition() + adder;
    if (cur_map->CoordsAreInBounds(targ_pos))
    {
        cur_char->Warp(cur_map, targ_pos);
        std::cout << "Moved to: " << targ_pos.x << "/" << targ_pos.y << std::endl;
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
