#include "gamestateaccountcreationawaitresponse.hpp"

void GameStateAccountCreationAwaitResponse::Render()
{
    this->game->DrawScreens();
}

void GameStateAccountCreationAwaitResponse::HandlePacket(PacketBase* packet)
{
    if(packet->GetType() == PacketBase::PACKET_REGISTRATION_RESPONSE)
    {
        PacketRegistrationResponse * response = static_cast<PacketRegistrationResponse*>(packet);
        //std::cout << "recieved packet with response: " << response->GetResponse() << std::endl;
        if(response->GetResponse() == PacketRegistrationResponse::RESPONSE_ACCOUNT_CREATED)
        {
            static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account creation successful.");
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
        else
        {
            if(response->GetResponse()== PacketRegistrationResponse::RESPONSE_ACCOUNT_ALREADY_EXISTS)
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account already exists.");
            else
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Unknown error creating account.");
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
    }
}

void GameStateAccountCreationAwaitResponse::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateAccountCreationAwaitResponse::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateAccountCreationAwaitResponse::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
