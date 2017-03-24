#include "gamestateinit.hpp"

#include <list>
#include <string>
#include <sstream>

#include "screenmaker.hpp"
#include "gamestatetitle.hpp"

#include "fontservice.hpp"
#include "bitmapservice.hpp"

#include "GameUtil/resourcefile.hpp"
#include "GameUtil/resource.hpp"

#include "allegro5/allegro_native_dialog.h"

GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

void GameStateInit::Tick()
{
    ALLEGRO_FONT* button_font = al_load_font("C:/Windows/Fonts/arial.ttf", 22, 0);
    FontService::Instance()->RegisterFont("title_button", button_font);

    ALLEGRO_BITMAP* title_bg = al_load_bitmap("resource/image/title_background.png");
    BitmapService::Instance()->RegisterBitmap("title_background", title_bg);

    ALLEGRO_BITMAP* base_bitmap = al_get_target_bitmap();

    try
    {
        std::list<Resource*> rlist;

        ResourceFile rfile;
        rfile.Open("tile");
        rlist = rfile.Read();
        rfile.Close();

        int c = 0;
        while (!rlist.empty())
        {
            Resource* resource = rlist.front();
            rlist.pop_front();

            uint32_t width = resource->GetWidth();
            uint32_t height = resource->GetHeight();

            ALLEGRO_BITMAP* bitmap = al_create_bitmap(width, height);
            al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

            al_set_target_bitmap(bitmap);

            for (uint32_t w = 0; w < width; w++)
            {
                for (uint32_t h = 0; h < height; h++)
                {
                    Pixel pixel = resource->GetPixel(w, h);
                    al_put_pixel(w,  h, al_map_rgba(pixel.r, pixel.g, pixel.b, pixel.a));
                }
            }

            al_unlock_bitmap(bitmap);
            delete resource;

            std::stringstream ss;
            ss << "tile_" << c;

            al_convert_mask_to_alpha(bitmap, al_map_rgb(0, 0, 0));
            BitmapService::Instance()->RegisterBitmap(ss.str(), bitmap);

            c++;
        }
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



    this->game->display = al_create_display(640, 480);
    if (!this->game->display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        throw "break";
    }

    al_register_event_source(this->game->event_queue, al_get_display_event_source(this->game->display));

    al_set_window_position(this->game->display, 100, 100);




    ScreenMakerTitle maker(this->game);
    GuiScreen* screen = maker.MakeScreen();
    this->game->PushScreen(screen);
    this->game->ChangeState(new GameStateTitle(this->game));
}
