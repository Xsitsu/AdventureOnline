#include "gamestateaccountcreation.hpp"
#include "gamestatetitlemake.hpp"

GameStateAccountCreation::GameStateAccountCreation(Game* game) : GameStateBase(game)
{

}

GameStateAccountCreation::~GameStateAccountCreation()
{

}
void GameStateAccountCreation::HandlePacket(PacketBase* packet)
{
    if(packet->GetType() == PacketBase::PACKET_REGISTRATION_RESPONSE)
    {
        PacketRegistrationResponse * response = static_cast<PacketRegistrationResponse*>(packet);
        if(response == 0)
        {
            game->PopScreen();
            game->ChangeState(new GameStateTitleMake(game));
        }
    }
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
