#include "gamestateserverconnect.hpp"

#include "gamestatetitle.hpp"
#include "gamestatequit.hpp"

#include "screenmaker.hpp"

#include <allegro5/allegro_native_dialog.h>

GameStateServerConnect::GameStateServerConnect(Game* game) : GameStateBase(game), start_time(std::time(NULL))
{

}

void GameStateServerConnect::Enter()
{
    this->game->client->SendConnectRequest();
}

void GameStateServerConnect::Exit()
{

}

void GameStateServerConnect::Tick()
{
    bool got_response = this->game->client->GetConnectResponse();
    if (got_response)
    {
        if (this->game->client->IsConnected())
        {
            ScreenMakerTitle maker(this->game);
            GuiScreen* screen = maker.MakeScreen();
            this->game->PushScreen(screen);
            this->game->ChangeState(new GameStateTitle(this->game));
        }
        else
        {
            al_show_native_message_box(this->game->display, "Connection Refused", "Could Not Connect To Server",
                                   "The server refused the connection. Please try again at a later time.",
                                   0, ALLEGRO_MESSAGEBOX_ERROR);

            this->game->ChangeState(new GameStateQuit(this->game));
        }
    }
    else if (std::time(NULL) - this->start_time > this->CONNECT_TIMEOUT)
    {
        al_show_native_message_box(this->game->display, "Connection Error", "Could Not Connect To Server",
                                   "The server could not be found. Please try again at a later time.",
                                   0, ALLEGRO_MESSAGEBOX_ERROR);

        this->game->ChangeState(new GameStateQuit(this->game));
    }
}

void GameStateServerConnect::Render()
{

}
