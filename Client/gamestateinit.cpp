#include "gamestate.hpp"

GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

void GameStateInit::Enter()
{

}

void GameStateInit::Exit()
{

}

void GameStateInit::Tick()
{
    this->game->ChangeState(new GameStateTitle(this->game));
}

void GameStateInit::Render()
{

}

void GameStateInit::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{

}
