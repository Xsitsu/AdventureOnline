#include "guitextelement.hpp"

GuiTextElement::GuiTextElement() : text_align(ALIGN_LEFT), text_color(Color3()),
text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)), text_draw_font(nullptr)
{}

GuiTextElement::~GuiTextElement()
{

}

std::string GuiTextElement::GetText() const
{
    return this->text;
}

void GuiTextElement::SetText(std::string text)
{
    this->text = text;
}

Color3 GuiTextElement::GetTextColor() const
{
    return this->text_color;
}

void GuiTextElement::SetTextColor(Color3 color)
{
    this->text_color = color;
    this->UpdateTextDrawColor();
}

unsigned char GuiTextElement::GetTextAlpha() const
{
    return this->text_alpha;
}

void GuiTextElement::SetTextAlpha(unsigned char trans)
{
    this->text_alpha = trans;
    this->UpdateTextDrawColor();
}

GuiTextElement::TextAlign GuiTextElement::GetTextAlign() const
{
    return this->text_align;
}

void GuiTextElement::SetTextAlign(GuiTextElement::TextAlign align)
{
    this->text_align = align;
}

ALLEGRO_FONT* GuiTextElement::GetTextFont() const
{
    return this->text_draw_font;
}

void GuiTextElement::SetTextFont(ALLEGRO_FONT* font)
{
    this->text_draw_font = font;
}

void GuiTextElement::UpdateTextDrawColor()
{
    Color3* color = &this->text_color;
    this->text_draw_color = al_map_rgba(color->r, color->g, color->b, this->text_alpha);
}
