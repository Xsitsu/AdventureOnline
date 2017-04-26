#include "guiobject.hpp"

#include <iostream>

GuiObject::GuiObject() : GuiBase(), is_filled(true), background_color(Color3()),
background_alpha(255), bg_draw_color(al_map_rgb(0, 0, 0))
{}

GuiObject::GuiObject(Vector2 size) : GuiBase(size), is_filled(true), background_color(Color3()),
background_alpha(255), bg_draw_color(al_map_rgb(0, 0, 0))
{}

GuiObject::GuiObject(Vector2 size, Vector2 position) : GuiBase(size, position), is_filled(true),
background_color(Color3()), background_alpha(255), bg_draw_color(al_map_rgb(0, 0, 0))
{}


GuiObject::GuiObject(const GuiObject& rhs) : GuiBase(rhs), is_filled(rhs.is_filled),
background_color(rhs.background_color), background_alpha(rhs.background_alpha),
bg_draw_color(rhs.bg_draw_color)
{

}

GuiObject& GuiObject::operator=(const GuiObject& rhs)
{
    if (this != &rhs)
    {
        GuiBase::operator=(rhs);
        this->is_filled = rhs.is_filled;
        this->background_color = rhs.background_color;
        this->background_alpha = rhs.background_alpha;
        this->bg_draw_color = rhs.bg_draw_color;
    }

    return *this;
}

GuiObject::~GuiObject()
{

}

void GuiObject::DoDraw() const
{
    Vector2 absolute_position = this->GetAbsolutePosition();
    int pos_x, pos_y, size_x, size_y;
    pos_x = absolute_position.x;
    pos_y = absolute_position.y;
    size_x = this->size.x;
    size_y = this->size.y;

    int rx = this->rounding.x;
    int ry = this->rounding.y;

    if (this->is_filled)
    {
        al_draw_filled_rounded_rectangle(pos_x, pos_y, pos_x + size_x, pos_y + size_y, rx, ry, this->bg_draw_color);
    }
    else
    {
        al_draw_rounded_rectangle(pos_x, pos_y, pos_x + size_x, pos_y + size_y, rx, ry, this->bg_draw_color, 2);
    }
}

bool GuiObject::GetIsFilled() const
{
    return this->is_filled;
}

void GuiObject::SetIsFilled(bool val)
{
    this->is_filled = val;
}

Color3 GuiObject::GetBackgroundColor() const
{
    return this->background_color;
}

void GuiObject::SetBackgroundColor(Color3 color)
{
    this->background_color = color;
    this->UpdateBackgroundDrawColor();
}

unsigned char GuiObject::GetBackgroundAlpha() const
{
    return this->background_alpha;
}

void GuiObject::SetBackgroundAlpha(unsigned char alpha)
{
    this->background_alpha = alpha;
    this->UpdateBackgroundDrawColor();
}

void GuiObject::UpdateBackgroundDrawColor()
{
    Color3* color = &this->background_color;
    this->bg_draw_color = al_map_rgba(color->r, color->g, color->b, this->background_alpha);
}

Vector2 GuiObject::GetRounding() const
{
    return this->rounding;
}

void GuiObject::SetRounding(Vector2 rounding)
{
    this->rounding = rounding;
}
