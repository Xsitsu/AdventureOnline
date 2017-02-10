#include "fontservice.hpp"

#include <iostream>

FontService* FontService::instance = NULL;

ALLEGRO_FONT* FontService::GetFont()
{
    if (!this->font)
    {
        font = al_load_font("C:/Windows/Fonts/arial.ttf", 18, 0);
        //font = al_load_ttf_font("arial.ttf", 18, 0);
    }

    return font;
}
