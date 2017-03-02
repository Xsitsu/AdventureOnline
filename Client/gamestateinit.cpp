#include "gamestateinit.hpp"

#include "screenmaker.hpp"
#include "gamestatetitle.hpp"

GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

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

    ScreenMakerTitle maker(this->game);
    GuiScreen* screen = maker.MakeScreen();
    this->game->PushScreen(screen);
    this->game->ChangeState(new GameStateTitle(this->game));
}
