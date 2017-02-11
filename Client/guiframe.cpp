#include "guiframe.hpp"

#include <iostream>

GuiFrame::GuiFrame() : GuiBase(), is_filled(true), background_color(Color3()), background_alpha(255), bg_draw_color(al_map_rgb(0, 0, 0))
{}

GuiFrame::GuiFrame(Vector2 size) : GuiBase(size), is_filled(true), background_color(Color3()), background_alpha(255), bg_draw_color(al_map_rgb(0, 0, 0))
{}

GuiFrame::GuiFrame(Vector2 size, Vector2 position) : GuiBase(size, position), is_filled(true), background_color(Color3()), background_alpha(0), bg_draw_color(al_map_rgb(0, 0, 0))
{}

GuiFrame::~GuiFrame()
{

}

void GuiFrame::DoDraw() const
{
    Vector2 absolute_position = this->GetAbsolutePosition();
    int pos_x, pos_y, size_x, size_y;
    pos_x = absolute_position.x;
    pos_y = absolute_position.y;
    size_x = this->size.x;
    size_y = this->size.y;

    if (this->is_filled)
    {
        al_draw_filled_rectangle(pos_x, pos_y, size_x + pos_x, size_y + pos_y, this->bg_draw_color);
    }
    else
    {
        al_draw_rectangle(pos_x, pos_y, size_x + pos_x, size_y + pos_y, this->bg_draw_color, 2);
    }
}

bool GuiFrame::GetIsFilled() const
{
    return this->is_filled;
}

void GuiFrame::SetIsFilled(bool val)
{
    this->is_filled = val;
}

Color3 GuiFrame::GetBackgroundColor() const
{
    return this->background_color;
}

void GuiFrame::SetBackgroundColor(Color3 color)
{
    this->background_color = color;
    this->UpdateBackgroundDrawColor();
}

unsigned char GuiFrame::GetBackgroundAlpha() const
{
    return this->background_alpha;
}

void GuiFrame::SetBackgroundAlpha(unsigned char alpha)
{
    this->background_alpha = alpha;
    this->UpdateBackgroundDrawColor();
}

void GuiFrame::UpdateBackgroundDrawColor()
{
    Color3* color = &this->background_color;
    this->bg_draw_color = al_map_rgba(color->r, color->g, color->b, this->background_alpha);
}
