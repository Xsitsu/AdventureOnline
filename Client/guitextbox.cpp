#include "guitextbox.hpp"

GuiTextBox::GuiTextBox() : GuiFrame(), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false), text_align(ALIGN_LEFT), text_draw_font(NULL)
{}

GuiTextBox::GuiTextBox(Vector2 size) : GuiFrame(size), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false), text_align(ALIGN_LEFT), text_draw_font(NULL)
{}

GuiTextBox::GuiTextBox(Vector2 size, Vector2 position) : GuiFrame(size, position), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false), text_align(ALIGN_LEFT), text_draw_font(NULL)
{}

GuiTextBox::~GuiTextBox()
{

}

std::string GuiTextBox::GetText() const
{
    return this->text;
}

void GuiTextBox::SetText(std::string text)
{
    this->text = text;
    this->AddCursorPosition(0); // reset cursor bounds
}

Color3 GuiTextBox::GetTextColor() const
{
    return this->text_color;
}

void GuiTextBox::SetTextColor(Color3 color)
{
    this->text_color = color;
    this->UpdateTextDrawColor();
}

unsigned char GuiTextBox::GetTextAlpha() const
{
    return this->text_alpha;
}

void GuiTextBox::SetTextAlpha(unsigned char trans)
{
    this->text_alpha = trans;
    this->UpdateTextDrawColor();
}

GuiTextBox::TEXTALIGN GuiTextBox::GetTextAlign() const
{
    return this->text_align;
}

void GuiTextBox::SetTextAlign(GuiTextBox::TEXTALIGN align)
{
    this->text_align = align;
}

ALLEGRO_FONT* GuiTextBox::GetTextFont() const
{
    return this->text_draw_font;
}

void GuiTextBox::SetTextFont(ALLEGRO_FONT* font)
{
    this->text_draw_font = font;
}

void GuiTextBox::UpdateTextDrawColor()
{
    Color3* color = &this->text_color;
    this->text_draw_color = al_map_rgba(color->r, color->g, color->b, this->text_alpha);
}

void GuiTextBox::DoDraw() const
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

        if (this->is_selected)
        {
            std::string sub = this->text.substr(0, this->cursor_position);
            int text_width = al_get_text_width(font, sub.c_str());

            int xPos = abs_pos.x;

            if (this->text_align != ALIGN_LEFT)
            {
                int full_width = al_get_text_width(font, this->text.c_str());

                if (this->text_align == ALIGN_CENTER)
                {
                    xPos += (this->size.x - full_width) / 2;
                }
                else
                {
                    xPos += (this->size.x - full_width);
                }
            }

            xPos += text_width;

            al_draw_line(xPos, mid_y, xPos, mid_y + font->height, al_map_rgb(255, 0, 255), 2);
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
    this->cursor_position = this->text.size();
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

    this->DoCharacterType(c);
}

void GuiTextBox::DoBackspace()
{
    int use_erase = this->cursor_position - 1;
    if (use_erase >= 0)
    {
        this->text.erase(use_erase, 1);
        this->cursor_position--;
    }

}

void GuiTextBox::AddCursorPosition(int pos)
{
    int cp = this->cursor_position + pos;
    int s = this->text.length();
    this->cursor_position = std::min(std::max(cp, 0), s);
}

