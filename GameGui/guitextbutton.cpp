#include "guitextbutton.hpp"
#include "allegro5/allegro_font.h"

GuiTextButton::GuiTextButton() : GuiButton(), GuiTextElement()
{}

GuiTextButton::GuiTextButton(Vector2 size) : GuiButton(size), GuiTextElement()
{}

GuiTextButton::GuiTextButton(Vector2 size, Vector2 position) : GuiButton(size, position), GuiTextElement()
{}

GuiTextButton::~GuiTextButton()
{

}

void GuiTextButton::DoDraw() const
{
    GuiButton::DoDraw();

    Vector2 abs_pos = this->GetAbsolutePosition();
    ALLEGRO_FONT* font = this->text_draw_font;
    if (font)
    {
        int draw_x = abs_pos.x;
        int align = 0;
        if (this->text_align == ALIGN_CENTER)
        {
            draw_x += (this->size.x / 2);
            align = ALLEGRO_ALIGN_CENTER;
        }
        else if (this->text_align == ALIGN_RIGHT)
        {
            draw_x += this->size.x;
            align = ALLEGRO_ALIGN_RIGHT;
        }
        int mid_y = abs_pos.y + (this->size.y / 2) - (al_get_font_line_height(font) / 2);
        al_draw_text(font, this->text_draw_color, draw_x, mid_y, align, this->text.c_str());
    }

}

void GuiTextButton::DoClick()
{
    GuiButtonArgs args;
    args.button = this;
    this->onClick.Fire(&args);
}

void GuiTextButton::DoMouseDown()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseDown.Fire(&args);
}

void GuiTextButton::DoMouseUp()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseUp.Fire(&args);
}

void GuiTextButton::DoMouseEnter()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseEnter.Fire(&args);
}

void GuiTextButton::DoMouseLeave()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseLeave.Fire(&args);
}
