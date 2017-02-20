#include "guitextbutton.hpp"

GuiTextButton::GuiTextButton() : GuiButton(), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)), text_draw_font(NULL)
{}

GuiTextButton::GuiTextButton(Vector2 size) : GuiButton(size), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)), text_draw_font(NULL)
{}

GuiTextButton::GuiTextButton(Vector2 size, Vector2 position) : GuiButton(size, position), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)), text_draw_font(NULL)
{}

GuiTextButton::~GuiTextButton()
{

}

std::string GuiTextButton::GetText() const
{
    return this->text;
}

void GuiTextButton::SetText(std::string text)
{
    this->text = text;
}

Color3 GuiTextButton::GetTextColor() const
{
    return this->text_color;
}

void GuiTextButton::SetTextColor(Color3 color)
{
    this->text_color = color;
    this->UpdateTextDrawColor();
}

unsigned char GuiTextButton::GetTextAlpha() const
{
    return this->text_alpha;
}

void GuiTextButton::SetTextAlpha(unsigned char trans)
{
    this->text_alpha = trans;
    this->UpdateTextDrawColor();
}

GuiTextButton::TEXTALIGN GuiTextButton::GetTextAlign() const
{
    return this->text_align;
}

void GuiTextButton::SetTextAlign(GuiTextButton::TEXTALIGN align)
{
    this->text_align = align;
}

ALLEGRO_FONT* GuiTextButton::GetTextFont() const
{
    return this->text_draw_font;
}

void GuiTextButton::SetTextFont(ALLEGRO_FONT* font)
{
    this->text_draw_font = font;
}

void GuiTextButton::UpdateTextDrawColor()
{
    Color3* color = &this->text_color;
    this->text_draw_color = al_map_rgba(color->r, color->g, color->b, this->text_alpha);
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
        int mid_y = abs_pos.y + (this->size.y / 2) - (font->height / 2);
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
