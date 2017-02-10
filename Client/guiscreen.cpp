#include "guiscreen.hpp"

GuiScreen::GuiScreen(GuiBase* base) : base(base)
{

}

GuiScreen::GuiScreen(GuiBase* base, std::list<GuiButton*> buttons) : base(base), buttons(buttons)
{

}

GuiScreen::~GuiScreen()
{
    delete this->base;
}

bool GuiScreen::HandleMouseDown(const Vector2& pos)
{
    bool was_sunk = false;
    button_iter iter = this->buttons.begin();

    while (!was_sunk && iter != this->buttons.end())
    {
        GuiButton* button = *iter;
        if (button->PointIsInBounds(pos))
        {
            was_sunk = true;
            button->DoClick();
        }
        else
        {
            ++iter;
        }
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseUp(const Vector2& pos)
{
    bool was_sunk = false;
    button_iter iter = this->buttons.begin();
    while (!was_sunk && iter != this->buttons.end())
    {
        GuiButton* button = *iter;
        if (button->PointIsInBounds(pos))
        {
            was_sunk = true;
            //button->DoClick();
        }
        else
        {
            ++iter;
        }
    }
    return was_sunk;
}

void GuiScreen::Draw()
{
    this->base->Draw();
}
