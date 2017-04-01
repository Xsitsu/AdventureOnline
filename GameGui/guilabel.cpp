#include "guilabel.hpp"

GuiLabel::GuiLabel()
{

}

GuiLabel::GuiLabel(Vector2 size) : GuiObject(size)
{

}

GuiLabel::GuiLabel(Vector2 size, Vector2 position) : GuiObject(size, position)
{

}

GuiLabel::GuiLabel(const GuiLabel& rhs) : GuiObject(rhs)
{

}

GuiLabel& GuiLabel::operator=(const GuiLabel& rhs)
{
    if (this != &rhs)
    {
        GuiObject::operator=(rhs);
    }

    return *this;
}

GuiLabel::~GuiLabel()
{

}

void GuiLabel::DoDraw() const
{
    GuiObject::DoDraw();
}
