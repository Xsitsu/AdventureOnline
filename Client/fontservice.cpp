#include "fontservice.hpp"

#include <iostream>

FontService* FontService::instance = NULL;

#ifdef WINDOWS
std::string FontService::FONT_PATH = "C:/Windows/Fonts/";
std::string FontService::DEBUG_FONT = "arial.ttf";
#endif // WINDOWS

#ifdef LINUX
std::string FontService::FONT_PATH = "/usr/share/fonts/";
std::string FontService::DEBUG_FONT = "gnu-free/FreeSans.otf";
#endif // LINUX

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
