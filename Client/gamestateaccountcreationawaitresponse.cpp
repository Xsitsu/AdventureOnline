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
        std::cout << "recieved packet with response: " << response->GetResponse() << std::endl;
        if(response->GetResponse() == PacketRegistrationResponse::RESPONSE_ACCOUNT_CREATED)
        {
            std::cout << "Account created successfully" << std::endl;
            static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account creation successful.");
            //game->GetCurrentScreen()->GetGuiById("success")->SetVisible(true);
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
        else
        {
            std::cout << "Account creation failed" << std::endl;
            if(response->GetResponse()== PacketRegistrationResponse::RESPONSE_ACCOUNT_ALREADY_EXISTS)
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Account already exists.");
            else
                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Unknown error creating account.");
            //game->GetCurrentScreen()->GetGuiById("failure")->SetVisible(true);
            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
    }
}
