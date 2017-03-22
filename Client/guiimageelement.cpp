#include "guiimageelement.hpp"

GuiImageElement::GuiImageElement() : image(nullptr), image_tint(Color3(255, 255, 255))
{
    this->UpdateTintDrawColor();
}

GuiImageElement::~GuiImageElement()
{

}

void GuiImageElement::SetImage(ALLEGRO_BITMAP* image)
{
    this->image = image;
}

ALLEGRO_BITMAP* GuiImageElement::GetImage() const
{
    return this->image;
}

void GuiImageElement::SetImageTint(const Color3& image_tint)
{
    this->image_tint = image_tint;
    this->UpdateTintDrawColor();
}

Color3 GuiImageElement::GetImageTint() const
{
    return this->image_tint;
}

void GuiImageElement::UpdateTintDrawColor()
{
    // ToDo: Maybe eventually look into seeing what happens when alpha is changed for a tinted bitmap.
    Color3* color = &this->image_tint;
    this->tint_draw_color = al_map_rgba(color->r, color->g, color->b, 255);
}
