#include "gamestate.hpp"

GameStateBase::GameStateBase(Game* game) : game(game)
{}



GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

void GameStateInit::Enter()
{

}

void GameStateInit::Exit()
{

}

void GameStateInit::Tick()
{
    this->game->ChangeState(new GameStateTitle(this->game));
}

void GameStateInit::Render()
{

}



GameStateTitle::GameStateTitle(Game* game) : GameStateBase(game)
{}

void GameStateTitle::Enter()
{
    this->game->display = al_create_display(640, 480);
    if (!this->game->display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        throw "break";
    }

    al_register_event_source(this->game->event_queue, al_get_display_event_source(this->game->display));

    al_set_window_position(this->game->display, 100, 100);
}

void GameStateTitle::Exit()
{

}

void GameStateTitle::Tick()
{

}

void GameStateTitle::Render()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
}
