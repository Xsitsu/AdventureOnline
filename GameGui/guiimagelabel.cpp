#include "guiimagelabel.hpp"

GuiImageLabel::GuiImageLabel() : GuiLabel(), GuiImageElement()
{}

GuiImageLabel::GuiImageLabel(Vector2 size) : GuiLabel(size), GuiImageElement()
{}

GuiImageLabel::GuiImageLabel(Vector2 size, Vector2 position) : GuiLabel(size, position), GuiImageElement()
{}

GuiImageLabel::~GuiImageLabel()
{}

void GuiImageLabel::DoDraw() const
{
    GuiLabel::DoDraw();

    if (this->image)
    {
        Vector2 start_pos = this->GetAbsolutePosition();
        Vector2 draw_size = this->size;

        Vector2 image_start_pos = Vector2(0, 0);
        Vector2 image_end_pos = Vector2(al_get_bitmap_width(this->image), al_get_bitmap_height(this->image));

        // Note: Since all bitmaps are ALWAYS drawn with their entire region, this image start and end pos
        // should still work even though the chance of it being a parallel to the start_pos draw_size is
        // high. This wont be changed now, but in the future if you ever encounter weird behavior with
        // region drawing for this class object, this is probably the reason.

        al_draw_tinted_scaled_bitmap(this->image, this->tint_draw_color,
                                     image_start_pos.x, image_start_pos.y, image_end_pos.x, image_end_pos.y,
                                     start_pos.x, start_pos.y, draw_size.x, draw_size.y,
                                     0);
    }
}
