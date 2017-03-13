#include "gamestateplaying.hpp"

#include "allegro5/allegro_image.h"

#include "bitmapservice.hpp"

GameStatePlaying::GameStatePlaying(Game* game) : GameStateBase(game)
{

}

void GameStatePlaying::Enter()
{
    this->game->current_map = new Map();
}

void GameStatePlaying::Exit()
{
    delete this->game->current_map;
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
    for (int x = current_pos.x - 4; x < current_pos.x + 4; x++)
    {
        for (int y = current_pos.y - 4; y < current_pos.y + 4; y++)
        {
            if (current_map->CoordsAreInBounds(Vector2(x, y)))
            {
                MapTile& tile = current_map->GetTile(Vector2(x, y));

                std::string bitmap_name = "tile_";
                bitmap_name += tile.GetSpriteId();
                ALLEGRO_BITMAP* tile_bitmap = BitmapService::Instance()->GetBitmap(bitmap_name);
                if (tile_bitmap)
                {
                    al_draw_bitmap(tile_bitmap, 0, 0, 0);
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
