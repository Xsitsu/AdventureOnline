#include "guiimagelabel.hpp"

GuiImageLabel::GuiImageLabel() : GuiFrame(), GuiImageElement()
{}

GuiImageLabel::GuiImageLabel(Vector2 size) : GuiFrame(size), GuiImageElement()
{}

GuiImageLabel::GuiImageLabel(Vector2 size, Vector2 position) : GuiFrame(size, position), GuiImageElement()
{}

GuiImageLabel::~GuiImageLabel()
{}

void GuiImageLabel::DoDraw() const
{
    GuiFrame::DoDraw();

    if (this->image)
    {
        Vector2 start_pos = this->GetAbsolutePosition();
        Vector2 end_pos = start_pos + this->size;

        Vector2 image_start_pos = Vector2(0, 0);
        Vector2 image_end_pos = Vector2(al_get_bitmap_width(this->image), al_get_bitmap_height(this->image));

        al_draw_tinted_scaled_bitmap(this->image, this->tint_draw_color,
                                     image_start_pos.x, image_start_pos.y, image_end_pos.x, image_end_pos.y,
                                     start_pos.x, start_pos.y, end_pos.x, end_pos.y,
                                     0);
    }
}
