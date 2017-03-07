#include "gamestateaccountcreation.hpp"
#include "screenmaker.hpp"
#include "gamestatetitle.hpp"

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
        if(response->GetResponse() == PacketRegistrationResponse::RESPONSE_ACCOUNT_CREATED)
        {
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
            static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account creation successful.");
            //game->GetCurrentScreen()->GetGuiById("success")->SetVisible(true);
        }
        else
        {
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
            if(response->GetResponse()== PacketRegistrationResponse::RESPONSE_ACCOUNT_ALREADY_EXISTS)
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account already exists.");
            else
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Unknown error creating account.");
            //game->GetCurrentScreen()->GetGuiById("failure")->SetVisible(true);
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
