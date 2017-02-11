#ifndef GUITEXTBUTTON_HPP_INCLUDE
#define GUITEXTBUTTON_HPP_INCLUDE

#include <string>

#include "guibutton.hpp"
#include "color3.hpp"

#include "allegro5/allegro_font.h"

#include "fontservice.hpp"

class GuiTextButton : public GuiButton
{
public:
    enum TEXTALIGN {ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER};

protected:
    std::string text;
    TEXTALIGN text_align;

    Color3 text_color;
    unsigned char text_alpha;

    ALLEGRO_COLOR text_draw_color;

    void UpdateTextDrawColor();

    virtual void DoDraw() const;

public:
    GuiTextButton();
    GuiTextButton(Vector2 size);
    GuiTextButton(Vector2 size, Vector2 position);
    virtual ~GuiTextButton();

    std::string GetText() const;
    void SetText(std::string text);

    Color3 GetTextColor() const;
    void SetTextColor(Color3 color);

    unsigned char GetTextAlpha() const;
    void SetTextAlpha(unsigned char trans);

    TEXTALIGN GetTextAlign() const;
    void SetTextAlign(TEXTALIGN align);


    virtual void DoClick();
    virtual void DoMouseEnter();
    virtual void DoMouseLeave();

};

struct SignalArgsGuiTextButton : SignalArgs
{
    GuiTextButton* button;
};

#endif // GUITEXTBUTTON_HPP_INCLUDE
