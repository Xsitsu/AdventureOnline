#include "gamestateinit.hpp"

#include "gamestatetitlemake.hpp"

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
    this->game->display = al_create_display(640, 480);
    if (!this->game->display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        throw "break";
    }

    al_register_event_source(this->game->event_queue, al_get_display_event_source(this->game->display));

    al_set_window_position(this->game->display, 100, 100);


    ALLEGRO_FONT* button_font = al_load_font("C:/Windows/Fonts/arial.ttf", 22, 0);
    FontService::Instance()->RegisterFont("title_button", button_font);

    this->game->ChangeState(new GameStateTitleMake(this->game));
}

void GameStateInit::Render()
{

}

void GameStateInit::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{

}
