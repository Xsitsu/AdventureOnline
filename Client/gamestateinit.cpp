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


    std::string use_font_name = FontService::FONT_PATH + FontService::DEBUG_FONT;


    ALLEGRO_FONT* button_font = al_load_font(use_font_name.c_str(), 22, 0);
    FontService::Instance()->RegisterFont("title_button", button_font);

    ALLEGRO_FONT* stat_bar_font = al_load_font(use_font_name.c_str(), 14, 0);
    FontService::Instance()->RegisterFont("stat_bar", stat_bar_font);

    ALLEGRO_FONT* actor_name_font = al_load_font(use_font_name.c_str(), 11, 0);
    FontService::Instance()->RegisterFont("actor_name", actor_name_font);


    ALLEGRO_BITMAP* base_bitmap = al_get_target_bitmap();



    try
    {
        ALLEGRO_COLOR mask_color = al_map_rgb(0, 0, 0);
        this->game->LoadResourceFile("resource0", BitmapService::BITMAPSET_BACKGROUND, mask_color);
        this->game->LoadResourceFile("resource1", BitmapService::BITMAPSET_TILE, mask_color);
        this->game->LoadResourceFile("resource2", BitmapService::BITMAPSET_CHARACTER, mask_color);
        this->game->LoadResourceFile("resource3", BitmapService::BITMAPSET_GUI_ELEMENT, mask_color);
        this->game->LoadResourceFile("resource4", BitmapService::BITMAPSET_HAIR_FEMALE, mask_color);
        this->game->LoadResourceFile("resource5", BitmapService::BITMAPSET_HAIR_MALE, mask_color);
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
