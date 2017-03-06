#include "gamestateloginawaitresponse.hpp"

#include "gamestatetitle.hpp"
#include "gamestatecharacterview.hpp"

#include "screenmaker.hpp"

#include "GameShared/packet.hpp"


void GameStateLoginAwaitResponse::Render()
{
    this->game->DrawScreens();
}

void GameStateLoginAwaitResponse::HandlePacket(PacketBase* packet)
{
    if (packet->GetType() == PacketBase::PACKET_LOGIN_RESPONSE)
    {
        PacketLoginResponse* response = static_cast<PacketLoginResponse*>(packet);
        PacketLoginResponse::LoginResponse res = response->GetResponse();

        if (res == PacketLoginResponse::LOGINRESPONSE_SUCCESS)
        {
            this->game->PopScreen();
            this->game->PopScreen();
            this->game->PopScreen();

            ScreenMakerCharacterView maker(this->game);
            GuiScreen* screen = maker.MakeScreen();

            this->game->PushScreen(screen);
            this->game->ChangeState(new GameStateCharacterView(this->game));
        }
        else if (res == PacketLoginResponse::LOGINRESPONSE_FAIL)
        {
            std::cout << "Invalid login credentials." << std::endl;
            this->game->PopScreen();
            this->game->ChangeState(new GameStateTitle(this->game));
        }
        else if (res == PacketLoginResponse::LOGINRESPONSE_ERROR)
        {
            std::cout << "Login failed due to unknown error." << std::endl;
            this->game->PopScreen();
            this->game->ChangeState(new GameStateTitle(this->game));
        }
    }
}


