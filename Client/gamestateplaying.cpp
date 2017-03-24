#include "gamestateplaying.hpp"

#include <string>
#include <fstream>
#include <sstream>

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

                std::stringstream ss;
                ss << "tile_";
                ss << tile.GetSpriteId();

                std::string bitmap_name = ss.str();

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
    Actor* self_actor = this->game->current_character;

    std::list<Actor*> actor_list = this->game->current_map->GetActorList();
    for (std::list<Actor*>::iterator iter = actor_list.begin(); iter != actor_list.end(); ++iter)
    {
        Actor* actor = *iter;
        if (actor != self_actor)
        {

        }
    }

    // Draw own character
    Character* mychar = this->game->current_character;
    Actor::Direction dir = mychar->GetDirection();
    Character::Gender gender = mychar->GetGender();
    Character::Skin skin = mychar->GetSkin();

    int draw_flags = 0;
    int dir_flag = 0;

    if (dir == Actor::DIR_RIGHT || dir == Actor::DIR_UP)
    {
        draw_flags = ALLEGRO_FLIP_HORIZONTAL;
    }

    if (dir == Actor::DIR_LEFT || dir == Actor::DIR_UP)
    {
        dir_flag = 1;
    }

    int sprite_width = 18;
    int sprite_height = 58;

    int draw_x = (sprite_width * 2 * (int)gender) + (sprite_width * dir_flag);
    int draw_y = (sprite_height * (int)skin);

    int dp_x = 640/2 - sprite_width/2;
    int dp_y = 480/2 - sprite_height/2;


    ALLEGRO_BITMAP* char_bitmap = BitmapService::Instance()->GetBitmap("character_0");
    al_draw_tinted_bitmap_region(char_bitmap, al_map_rgb(255, 255, 255),
                                 draw_x, draw_y, sprite_width, sprite_height,
                                 dp_x, dp_y, draw_flags);


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
    else
    {
        return;
    }

    Map* cur_map = this->game->current_map;
    Character* cur_char = this->game->current_character;

    cur_char->SetDirection(dir);

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
