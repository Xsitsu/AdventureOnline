#include "guitextbox.hpp"
#include <allegro5/allegro_font.h>.

GuiTextBox::GuiTextBox() : GuiObject(), GuiTextElement(), cursor_position(0), is_selected(false),
text_width(0), cursor_text_width(0)
{}

GuiTextBox::GuiTextBox(Vector2 size) : GuiObject(size), GuiTextElement(), cursor_position(0),
is_selected(false), text_width(0), cursor_text_width(0)
{}

GuiTextBox::GuiTextBox(Vector2 size, Vector2 position) : GuiObject(size, position), GuiTextElement(),
cursor_position(0), is_selected(false), text_width(0), cursor_text_width(0)
{}

GuiTextBox::~GuiTextBox()
{}

void GuiTextBox::SetText(std::string text)
{
    GuiTextElement::SetText(text);

    this->UpdateTextWidth();
    this->AddCursorPosition(0); // reset cursor bounds
}

void GuiTextBox::SetTextFont(ALLEGRO_FONT* font)
{
    GuiTextElement::SetTextFont(font);

    this->UpdateTextWidth();
}

void GuiTextBox::DoDraw() const
{
    GuiObject::DoDraw();

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
        int mid_y = abs_pos.y + (this->size.y / 2) - (al_get_font_line_height(font) / 2);
        al_draw_text(font, this->text_draw_color, draw_x, mid_y, align, this->text.c_str());

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

            al_draw_line(xPos, mid_y, xPos, mid_y + al_get_font_line_height(font), al_map_rgb(255, 0, 255), 2);
        }
    }

}

void GuiTextBox::RegisterOnSelect(ListenerBase<TextBoxSelectionArgs*>* listener)
{
    this->onSelect.Connect(listener);
}

void GuiTextBox::RegisterOnDeselect(ListenerBase<TextBoxSelectionArgs*>* listener)
{
    this->onDeselect.Connect(listener);
}

void GuiTextBox::RegisterOnCharacterType(ListenerBase<TextBoxTypingArgs*>* listener)
{
    this->onCharacterType.Connect(listener);
}

void GuiTextBox::DoSelect()
{
    this->SetCursorPosition(this->text.size());
    this->is_selected = true;

    TextBoxSelectionArgs args;
    args.text_box = this;
    this->onSelect.Fire(&args);
}

void GuiTextBox::DoDeselect()
{
    this->is_selected = false;

    TextBoxSelectionArgs args;
    args.text_box = this;
    this->onDeselect.Fire(&args);
}

void GuiTextBox::DoCharacterType(char c)
{
    TextBoxTypingArgs args;
    args.text_box = this;
    args.character = c;
    this->onCharacterType.Fire(&args);
}

void GuiTextBox::Select()
{
    GuiSelectionService* service = GuiSelectionService::Instance();
    if (service->GetSelectedTextBox() != this)
    {
        GuiSelectionService::Instance()->SelectTextBox(this);
    }
}

void GuiTextBox::Deselect()
{
    GuiSelectionService::Instance()->SelectTextBox(NULL);
}

void GuiTextBox::AddTextCharacter(char c)
{
    char ch[2];
    ch[0] = c;
    ch[1] = 0;
    this->text.insert(this->cursor_position, ch);
    this->cursor_position++;

    this->UpdateTextWidth();

    this->DoCharacterType(c);
}

void GuiTextBox::DoBackspace()
{
    int use_erase = this->cursor_position - 1;
    if (use_erase >= 0)
    {
        this->text.erase(use_erase, 1);
        this->cursor_position--;

        this->UpdateTextWidth();
    }

}

void GuiTextBox::AddCursorPosition(int pos)
{
    this->SetCursorPosition(this->cursor_position + pos);
}

void GuiTextBox::SetCursorPosition(int pos)
{
    int s = this->text.length(); // Does a needed implicit conversion by having it on its own line.
    this->cursor_position = std::min(std::max(pos, 0), s);

    this->UpdateCursorTextWidth();
}


void GuiTextBox::UpdateTextWidth()
{
    if (this->text_draw_font)
    {
        this->text_width = al_get_text_width(this->text_draw_font, this->text.c_str());
        this->UpdateCursorTextWidth();
    }
}

void GuiTextBox::UpdateCursorTextWidth()
{
    if (this->text_draw_font)
    {
        std::string sub = this->text.substr(0, this->cursor_position);
        this->cursor_text_width = al_get_text_width(this->text_draw_font, sub.c_str());
    }
}
