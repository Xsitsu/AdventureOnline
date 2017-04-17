#include "gamestateinit.hpp"

#include <list>
#include <string>
#include <sstream>

#include "screenmaker.hpp"
#include "gamestateserverconnect.hpp"
#include "gamestatequit.hpp"

#include "fontservice.hpp"
#include "bitmapservice.hpp"

#include "allegro5/allegro_native_dialog.h"

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

    ALLEGRO_BITMAP* base_bitmap = al_get_target_bitmap();

    try
    {
        ALLEGRO_COLOR mask_color = al_map_rgb(0, 0, 0);
        this->game->LoadResourceFile("resource0", "background_", mask_color);
        this->game->LoadResourceFile("resource1", "tile_", mask_color);
        this->game->LoadResourceFile("resource2", "character_", mask_color);
        this->game->LoadResourceFile("resource3", "guielement_", mask_color);
        this->game->LoadResourceFile("resource4", "hairf_", mask_color);
        this->game->LoadResourceFile("resource5", "hairm_", mask_color);
    }
    catch (FileException::FileException& e)
    {
        //std::cout << "error: " << e.what() << std::endl;

        al_show_native_message_box(nullptr, "Could Not Load Resource File",
                                  "A resource file is either corrupted or missing from your computer.",
                                   e.what(), 0, ALLEGRO_MESSAGEBOX_ERROR);

        this->game->ChangeState(new GameStateQuit(this->game));
        return;
    }


    al_set_target_bitmap(base_bitmap);

    this->game->ChangeState(new GameStateServerConnect(this->game));
}
