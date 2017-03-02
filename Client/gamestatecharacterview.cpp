#include "gamestatecharacterview.hpp"

#include "gamestatequit.hpp"

GameStateCharacterView::GameStateCharacterView(Game* game) : GameStateBase(game)
{

}

GameStateCharacterView::~GameStateCharacterView()
{

}

void GameStateCharacterView::Enter()
{

}

void GameStateCharacterView::Exit()
{

}

void GameStateCharacterView::Tick()
{

}

void GameStateCharacterView::Render()
{
    this->game->DrawScreens();
}

void GameStateCharacterView::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateCharacterView::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateCharacterView::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateCharacterView::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateCharacterView::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
