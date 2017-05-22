#ifndef GUITEXTELEMENT_HPP_INCLUDE
#define GUITEXTELEMENT_HPP_INCLUDE

#include <string>

#include "color3.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class
#ifdef WINDOWS
DLL_EXPORT
#endif
GuiTextElement
{
public:
    enum TextAlign {ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER};

protected:
    std::string text;
    TextAlign text_align;

    Color3 text_color;
    unsigned char text_alpha;

    ALLEGRO_COLOR text_draw_color;
    ALLEGRO_FONT* text_draw_font;

    void UpdateTextDrawColor();

public:
    GuiTextElement();
    virtual ~GuiTextElement();

    std::string GetText() const;
    virtual void SetText(std::string text);

    Color3 GetTextColor() const;
    virtual void SetTextColor(Color3 color);

    unsigned char GetTextAlpha() const;
    virtual void SetTextAlpha(unsigned char trans);

    TextAlign GetTextAlign() const;
    virtual void SetTextAlign(TextAlign align);

    ALLEGRO_FONT* GetTextFont() const;
    virtual void SetTextFont(ALLEGRO_FONT* font);
};

#endif // GUITEXTELEMENT_HPP_INCLUDE
