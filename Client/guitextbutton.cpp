#include "guitextbutton.hpp"

GuiTextButton::GuiTextButton() : GuiButton(), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0))
{}

GuiTextButton::GuiTextButton(Vector2 size) : GuiButton(size), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0))
{}

GuiTextButton::GuiTextButton(Vector2 size, Vector2 position) : GuiButton(size, position), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0))
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

void GuiTextButton::UpdateTextDrawColor()
{
    Color3* color = &this->text_color;
    this->text_draw_color = al_map_rgba(color->r, color->g, color->b, this->text_alpha);
}

void GuiTextButton::DoDraw() const
{
    GuiButton::DoDraw();

    Vector2 abs_pos = this->GetAbsolutePosition();
    ALLEGRO_FONT* font = FontService::Instance()->GetFont();
    if (font)
    {
        int mid_x = abs_pos.x + (this->size.x / 2);
        int mid_y = abs_pos.y + (this->size.y / 2) - (font->height / 2);
        al_draw_text(font, this->text_draw_color, mid_x, mid_y, ALLEGRO_ALIGN_CENTER, this->text.c_str());
    }

}

void GuiTextButton::DoClick()
{
    SignalArgsGuiTextButton args;
    args.button = this;
    this->onClick.Fire(&args);
}

void GuiTextButton::DoMouseEnter()
{
    SignalArgsGuiTextButton args;
    args.button = this;
    this->onMouseEnter.Fire(&args);
}

void GuiTextButton::DoMouseLeave()
{
    SignalArgsGuiTextButton args;
    args.button = this;
    this->onMouseLeave.Fire(&args);
}
