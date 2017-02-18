#include "gamestatequit.hpp"

GameStateQuit::GameStateQuit(Game* game) : GameStateBase(game)
{}

GameStateQuit::~GameStateQuit()
{

}

void GameStateQuit::Enter()
{

}

void GameStateQuit::Exit()
{

}

void GameStateQuit::Tick()
{
    this->game->is_running = false;
}

void GameStateQuit::Render()
{

}

void GameStateQuit::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateQuit::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateQuit::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateQuit::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateQuit::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{

}
