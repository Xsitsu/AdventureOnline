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

ALLEGRO_FONT* FontService::GetFont(std::string font_name)
{
    ALLEGRO_FONT* font = this->fonts[font_name];
    if (!font) throw FontNotLoadedException();
    return font;
}

void FontService::RegisterFont(std::string font_name, ALLEGRO_FONT* font)
{
    if (this->fonts[font_name]) throw FontAlreadyLoadedException();
    this->fonts[font_name] = font;
}

void FontService::UnregisterFont(std::string font_name)
{
    this->GetFont(font_name); // throws exception if not loaded
    this->fonts.erase(font_name);
}
