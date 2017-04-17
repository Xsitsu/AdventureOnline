#include "gamestatecharactercreationawaitresponse.hpp"
#include "gamestatecharacterview.hpp"
#include "gamestatecharactercreation.hpp"
#include "screenmaker.hpp"
void GameStateCharacterCreationAwaitResponse::Render()
{
    this->game->DrawScreens();
}

void GameStateCharacterCreationAwaitResponse::HandlePacket(PacketBase* packet)
{
    if(packet->GetType() == PacketBase::PACKET_CHARACTER_CREATE_RESPONSE)
    {
        PacketCharacterCreationResponse * response = static_cast<PacketCharacterCreationResponse *>(packet);
        //game->PopScreen();
        if(response->GetResponse() == PacketCharacterCreationResponse::RESPONSE_CHARACTER_CREATED)
        {
            game->PopScreen();
            game->PopScreen();
            ScreenMakerCharacterView maker(this->game);
            Character * temp = this->game->GetCurrentCharacter();
            delete temp;
            this->game->SetCurrentCharacter(nullptr);
            game->PushScreen(maker.MakeScreen());
            game->ChangeState(new GameStateCharacterView(this->game));
            //std::cout << "Account created successfully" << std::endl;
//            static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Character creation successful.");
            //game->GetCurrentScreen()->GetGuiById("success")->SetVisible(true);
//            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
        else
        {
            game->PopScreen();
            game->ChangeState(new GameStateCharacterCreation(this->game));
            //std::cout << "Account creation failed" << std::endl;
//            if(response->GetResponse()== PacketCharacterCreationResponse::RESPONSE_CHARACTER_ALREADY_EXISTS)
//                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Character name already in use.");
//            else
//                static_cast<GuiTextButton*>(game->GetCurrentScreen()->GetGuiById("Confirmation"))->SetText("Unknown error creating character.");
//            game->GetCurrentScreen()->GetGuiById("Continue")->SetVisible(true);
        }
    }
}

void GameStateCharacterCreationAwaitResponse::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateCharacterCreationAwaitResponse::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateCharacterCreationAwaitResponse::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
