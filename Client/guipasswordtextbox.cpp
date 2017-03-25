#include "guipasswordtextbox.hpp"

GuiPasswordTextBox::GuiPasswordTextBox() : GuiTextBox()
{}

GuiPasswordTextBox::GuiPasswordTextBox(Vector2 size) : GuiTextBox(size)
{}

GuiPasswordTextBox::GuiPasswordTextBox(Vector2 size, Vector2 position) : GuiTextBox(size, position)
{}

GuiPasswordTextBox::~GuiPasswordTextBox()
{}

void GuiPasswordTextBox::DoDraw() const
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
        al_draw_text(font, this->text_draw_color, draw_x, mid_y, align, this->draw_text.c_str());

        if (this->is_selected)
        {
            int xPos = abs_pos.x;

            if (this->text_align != ALIGN_LEFT)
            {
                if (this->text_align == ALIGN_CENTER)
                {
                    xPos += (this->size.x - this->text_width) / 2;
                }
                else
                {
                    xPos += (this->size.x - this->text_width);
                }
            }

            xPos += this->cursor_text_width;

            al_draw_line(xPos, mid_y, xPos, mid_y + font->height, al_map_rgb(255, 0, 255), 2);
        }
    }

}

void GuiPasswordTextBox::UpdateTextWidth()
{
    this->draw_text = "";
    for (unsigned int i = 0; i < this->text.size(); i++)
    {
        this->draw_text += "*";
    }

    if (this->text_draw_font)
    {
        this->text_width = al_get_text_width(this->text_draw_font, this->draw_text.c_str());
        this->UpdateCursorTextWidth();
    }
}

void GuiPasswordTextBox::UpdateCursorTextWidth()
{
    if (this->text_draw_font)
    {
        std::string sub = this->draw_text.substr(0, this->cursor_position);
        this->cursor_text_width = al_get_text_width(this->text_draw_font, sub.c_str());
    }
}
