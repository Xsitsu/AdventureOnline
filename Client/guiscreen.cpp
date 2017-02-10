#include "guiscreen.hpp"

GuiScreen::GuiScreen(GuiBase* base) : base(base), current_mouse_hover_button(NULL)
{

}

GuiScreen::GuiScreen(GuiBase* base, std::list<GuiButton*> buttons) : base(base), buttons(buttons), current_mouse_hover_button(NULL)
{

}

GuiScreen::~GuiScreen()
{
    delete this->base;
}

void GuiScreen::Draw()
{
    this->base->Draw();
}

void GuiScreen::RemoveButtonFromList(GuiButton* button)
{
    button_iter iter = this->buttons.begin();
    while (iter != this->buttons.end())
    {
        GuiButton* current = *iter;
        if (current == button)
        {
            this->buttons.erase(iter);
            return;
        }

        ++iter;
    }
}

GuiButton* GuiScreen::FindButtonCoveringPoint(const Vector2& pos)
{
    GuiButton* button = NULL;
    button_iter iter = this->buttons.begin();
    while (iter != this->buttons.end())
    {
        button = *iter;
        if (!button)
        {
            this->RemoveButtonFromList(button);
        }
        else if (!button->HasAncestor(this->base))
        {
            this->RemoveButtonFromList(button);
        }
        else if (button->GetVisible() && button->PointIsInBounds(pos))
        {
            return button;
        }

        ++iter;
    }

    return NULL;
}

bool GuiScreen::HandleMouseDown(const Vector2& pos)
{
    bool was_sunk = false;
    GuiButton* button = this->FindButtonCoveringPoint(pos);
    if (button)
    {
        button->DoClick();
        was_sunk = true;
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseUp(const Vector2& pos)
{
    bool was_sunk = false;
    GuiButton* button = this->FindButtonCoveringPoint(pos);
    if (button)
    {
        //button->DoClick();
        was_sunk = true;
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseMove(const Vector2& pos)
{
    bool was_sunk = false;
    GuiButton* button = this->FindButtonCoveringPoint(pos);

    if (this->current_mouse_hover_button)
    {
        if (button != this->current_mouse_hover_button)
        {
            this->current_mouse_hover_button->DoMouseLeave();

            this->current_mouse_hover_button = button;

            if (button)
            {
                this->current_mouse_hover_button->DoMouseEnter();
            }
        }
    }
    else if (button)
    {
        this->current_mouse_hover_button = button;
        this->current_mouse_hover_button->DoMouseEnter();
    }

    return was_sunk;
}
