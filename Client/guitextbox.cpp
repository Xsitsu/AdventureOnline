#include "guitextbox.hpp"

GuiTextBox::GuiTextBox() : GuiFrame(), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false)
{}

GuiTextBox::GuiTextBox(Vector2 size) : GuiFrame(size), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false)
{}

GuiTextBox::GuiTextBox(Vector2 size, Vector2 position) : GuiFrame(size, position), text_color(Color3()), text_alpha(255), text_draw_color(al_map_rgb(0, 0, 0)),
cursor_position(0), is_selected(false)
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

void GuiTextBox::UpdateTextDrawColor()
{
    Color3* color = &this->text_color;
    this->text_draw_color = al_map_rgba(color->r, color->g, color->b, this->text_alpha);
}

void GuiTextBox::DoDraw() const
{
    GuiFrame::DoDraw();

    Vector2 abs_pos = this->GetAbsolutePosition();
    ALLEGRO_FONT* font = FontService::Instance()->GetFont();
    if (font)
    {
        int mid_x = abs_pos.x + (this->size.x / 2);
        int mid_y = abs_pos.y + (this->size.y / 2) - (font->height / 2);
        al_draw_text(font, this->text_draw_color, mid_x, mid_y, ALLEGRO_ALIGN_CENTER, this->text.c_str());
    }

}

SignalListener GuiTextBox::RegisterOnSelect(signal_callback callback)
{
    return this->onSelect.Connect(callback);
}

SignalListener GuiTextBox::RegisterOnDeselect(signal_callback callback)
{
    return this->onDeselect.Connect(callback);
}

void GuiTextBox::DoSelect()
{
    this->cursor_position = 0;
    this->is_selected = true;

    SignalArgsGuiTextBox args;
    args.text_box = this;
    this->onSelect.Fire(&args);
}

void GuiTextBox::DoDeselect()
{
    this->is_selected = false;

    SignalArgsGuiTextBox args;
    args.text_box = this;
    this->onDeselect.Fire(&args);
}

void GuiTextBox::Select()
{
    GuiSelectionService::Instance()->SelectTextBox(this);
}

void GuiTextBox::Deselect()
{
    GuiSelectionService::Instance()->SelectTextBox(NULL);
}
