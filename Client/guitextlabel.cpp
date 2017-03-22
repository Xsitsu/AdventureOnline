#include "guitextlabel.hpp"

GuiTextLabel::GuiTextLabel() : GuiFrame(), GuiTextElement()
{}

GuiTextLabel::GuiTextLabel(Vector2 size) : GuiFrame(size), GuiTextElement()
{}

GuiTextLabel::GuiTextLabel(Vector2 size, Vector2 position) : GuiFrame(size, position), GuiTextElement()
{}

GuiTextLabel::~GuiTextLabel()
{}

void GuiTextLabel::DoDraw() const
{
    GuiFrame::DoDraw();

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
