#include "gamestateserverconnect.hpp"

#include "gamestateinit.hpp"
#include "gamestatequit.hpp"

#include <allegro5/allegro_native_dialog.h>

GameStateServerConnect::GameStateServerConnect(Game* game) : GameStateBase(game), start_time(std::time(NULL))
{

}

void GameStateServerConnect::Enter()
{
    this->game->display = al_create_display(120, 240);
    this->game->client->SendConnectRequest();
}

void GameStateServerConnect::Exit()
{
    al_destroy_display(this->game->display);
    this->game->display = NULL;
}

void GameStateServerConnect::Tick()
{
    if (this->game->client->IsConnected())
    {
        this->game->ChangeState(new GameStateInit(this->game));
    }
    else if (std::time(NULL) - this->start_time > this->CONNECT_TIMEOUT)
    {
        al_show_native_message_box(this->game->display, "Connection Error", "Could Not Connect To Server",
                                   "The server could not be found. Please try again at a later time.",
                                   0, ALLEGRO_MESSAGEBOX_ERROR);

        this->game->ChangeState(new GameStateQuit(this->game));
    }
    else
    {
        this->game->client->GetConnectResponse();
    }
}

void GameStateServerConnect::Render()
{

}
