#include "gamestatequit.hpp"

GameStateQuit::GameStateQuit(Game* game) : GameStateBase(game)
{}

void GameStateQuit::Enter()
{
    if (this->game->client->IsConnected())
    {
        this->game->client->SendDisconnectRequest();
    }
}

void GameStateQuit::Tick()
{
    if (this->game->client->IsConnected())
    {
        this->game->client->GetDisconnectResponse();
    }
    else
    {
        this->game->is_running = false;
    }
}
