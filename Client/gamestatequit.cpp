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
    if (!this->game->client->IsConnected())
    {
        this->game->is_running = false;
    }
}

void GameStateQuit::HandlePacket(PacketBase* packet)
{
    if (packet->GetType() == PacketBase::PACKET_DISCONNECT_RESPONSE)
    {
        this->game->client->FinalizeDisconnect();
    }
}
