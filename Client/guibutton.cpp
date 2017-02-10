#include "guibutton.hpp"

#include <iostream>

GuiButton::GuiButton() : GuiFrame()
{}

GuiButton::GuiButton(Vector2 size) : GuiFrame(size)
{}

GuiButton::GuiButton(Vector2 size, Vector2 position) : GuiFrame(size, position)
{}

GuiButton::~GuiButton()
{

}

void GuiButton::DoClick()
{
    this->onClick.Fire(NULL);
}
