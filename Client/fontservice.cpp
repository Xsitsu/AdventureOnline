#include "fontservice.hpp"

#include <iostream>

FontService* FontService::instance = NULL;

void FontService::LoadFonts()
{
    this->font = al_load_font("C:/Windows/Fonts/arial.ttf", 18, 0);
    //this->font = al_load_ttf_font("arial.ttf", 18, 0);
}

ALLEGRO_FONT* FontService::GetFont()
{
    return this->font;
}
