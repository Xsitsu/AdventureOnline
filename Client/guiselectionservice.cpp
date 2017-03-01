#include "guiselectionservice.hpp"

GuiSelectionService* GuiSelectionService::instance = NULL;

GuiSelectionService::GuiSelectionService() : selected_text_box(NULL), current_mouse_hover(NULL), current_button_down(NULL)
{
    memset(this->lowercase_keys, 0, ALLEGRO_KEY_MAX);
    memset(this->uppercase_keys, 0, ALLEGRO_KEY_MAX);

    this->InitKeyList();
}

void GuiSelectionService::InitKeyList()
{
    // Letters
    for (char c = 'a'; c <= 'z'; c++)
    {
        int index = ALLEGRO_KEY_A + (c - 'a');
        this->SetKey(index,  c, c - 32);
    }


    // Numbers
    char symbols[10] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '('};
    for (char c = '0'; c <= '9'; c++)
    {
        int i = (c - '0');
        int index = ALLEGRO_KEY_0 + i;
        this->SetKey(index, c, symbols[i]);
    }


    // Extras
    this->SetKey(ALLEGRO_KEY_SPACE, ' ', ' ');
    this->SetKey(ALLEGRO_KEY_BACKSLASH, '\\', '|');
    this->SetKey(ALLEGRO_KEY_COMMA,  ',', '<');
    this->SetKey(ALLEGRO_KEY_FULLSTOP, '.', '>'); // ALLEGRO_KEY_FULLSTOP is ALLEGRO_KEY_PERIOD
    this->SetKey(ALLEGRO_KEY_SLASH, '/', '?');
    this->SetKey(ALLEGRO_KEY_TILDE, '`', '~');
    this->SetKey(ALLEGRO_KEY_EQUALS, '=', '+');
    this->SetKey(ALLEGRO_KEY_MINUS, '-', '_');
    this->SetKey(ALLEGRO_KEY_OPENBRACE, '[', '{');
    this->SetKey(ALLEGRO_KEY_CLOSEBRACE, ']', '}');
    this->SetKey(ALLEGRO_KEY_SEMICOLON, ';', ':');
    this->SetKey(ALLEGRO_KEY_QUOTE, '\'', '\"');


}

void GuiSelectionService::SetKey(int index, char lower, char upper)
{
    this->lowercase_keys[index] = lower;
    this->uppercase_keys[index] = upper;
}

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

bool GuiSelectionService::CheckModifier(unsigned int modifiers, int modifier)
{
    return ((modifiers & modifier) == modifier);
}

char GuiSelectionService::AllegroKeycodeToAscii(int keycode, unsigned int modifiers)
{
    bool shift_mod = this->CheckModifier(modifiers, ALLEGRO_KEYMOD_SHIFT);
    bool caps_lock_mod = (this->CheckModifier(modifiers, ALLEGRO_KEYMOD_CAPSLOCK));

    char* case_set;
    if (shift_mod)
    {
        case_set = this->uppercase_keys;
    }
    else
    {
        case_set = this->lowercase_keys;
    }

    return case_set[keycode];
}

bool GuiSelectionService::TextBoxHasFocus()
{
    return (this->selected_text_box != NULL);
}

void GuiSelectionService::HandleKeyboardTyping(ALLEGRO_KEYBOARD_EVENT keyboard)
{
    if (this->selected_text_box)
    {
        if (keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
        {
            this->selected_text_box->DoBackspace();
        }
        else if (keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            this->selected_text_box->AddCursorPosition(-1);
        }
        else if (keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            this->selected_text_box->AddCursorPosition(1);
        }
        else if (keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            // do a thing
        }
        else
        {
            char c = this->AllegroKeycodeToAscii(keyboard.keycode, keyboard.modifiers);
            if (c != 0)
            {
                this->selected_text_box->AddTextCharacter(c);
            }
        }
    }
}

void GuiSelectionService::MouseButtonDown(GuiButton* button)
{
    this->current_button_down = button;
    button->DoMouseDown();
}

void GuiSelectionService::MouseButtonUp(GuiButton* button)
{
    if (this->current_button_down == button)
    {
        button->DoClick();
    }

    this->current_button_down = NULL;
    button->DoMouseUp();
}

void GuiSelectionService::LetMouseUp()
{
    if (this->current_button_down)
    {
        this->current_button_down = NULL;
    }
}

void GuiSelectionService::HandleCurrentScreenChanged()
{
    this->selected_text_box = NULL;
    this->current_mouse_hover = NULL;
    this->current_button_down = NULL;
}
