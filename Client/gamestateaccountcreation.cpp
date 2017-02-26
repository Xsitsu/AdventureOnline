#include "gamestateaccountcreation.hpp"

GameStateAccountCreation::GameStateAccountCreation(Game* game) : GameStateBase(game)
{

}

GameStateAccountCreation::~GameStateAccountCreation()
{

}

void GameStateAccountCreation::Enter()
{

}

void GameStateAccountCreation::Exit()
{

}

void GameStateAccountCreation::Tick()
{

}

void GameStateAccountCreation::Render()
{
    this->game->DrawScreens();
}

void GameStateAccountCreation::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateAccountCreation::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateAccountCreation::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateAccountCreation::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateAccountCreation::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
