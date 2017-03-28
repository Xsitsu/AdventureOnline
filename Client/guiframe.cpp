#include "guiframe.hpp"

GuiFrame::GuiFrame() : GuiObject()
{}

GuiFrame::GuiFrame(Vector2 size) : GuiObject(size)
{}

GuiFrame::GuiFrame(Vector2 size, Vector2 position) : GuiObject(size, position)
{}

GuiFrame::~GuiFrame()
{

}

void GuiFrame::DoDraw() const
{
    GuiObject::DoDraw();
}
