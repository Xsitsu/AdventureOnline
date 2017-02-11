#include "guiselectionservice.hpp"

GuiSelectionService* GuiSelectionService::instance = NULL;

GuiTextBox* GuiSelectionService::GetSelectedTextBox()
{
    return this->selected_text_box;
}

void GuiSelectionService::SelectTextBox(GuiTextBox* text_box)
{
    if (this->selected_text_box)
    {
        this->selected_text_box->DoDeselect();
    }

    this->selected_text_box = text_box;

    if (this->selected_text_box)
    {
        this->selected_text_box->DoSelect();
    }
}

GuiBase* GuiSelectionService::GetCurrentMouseHover()
{
    return this->current_mouse_hover;
}

void GuiSelectionService::SetCurrentMouseHover(GuiBase* hover)
{
    this->current_mouse_hover = hover;
}

void GuiSelectionService::HandleKeyboardTyping(ALLEGRO_KEYBOARD_EVENT keyboard)
{
    if (this->selected_text_box)
    {
        if (keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
        {
            this->selected_text_box->DoBackspace();
        }
        else if (keyboard.keycode >= ALLEGRO_KEY_A && keyboard.keycode <= ALLEGRO_KEY_Z)
        {
            char c = 'a';
            c += (keyboard.keycode - ALLEGRO_KEY_A);
            if (keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT == ALLEGRO_KEYMOD_SHIFT)
            {
                c -= 32;
            }
            this->selected_text_box->AddTextCharacter(c);
        }
        else if (keyboard.keycode >= ALLEGRO_KEY_0 && keyboard.keycode <= ALLEGRO_KEY_9)
        {
            char c = '0';
            c += (keyboard.keycode - ALLEGRO_KEY_0);
            this->selected_text_box->AddTextCharacter(c);
        }
        else if (keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            char c = ' ';
            this->selected_text_box->AddTextCharacter(c);
        }
        else if (keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            this->selected_text_box->AddCursorPosition(-1);
        }
        else if (keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            this->selected_text_box->AddCursorPosition(1);
        }

    }
}
