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


void GuiFrame::SetGuiId(std::string id, GuiBase* gui)
{
    if (!gui->HasAncestor(this))
    {
        throw "error";
    }

    this->gui_id_map[id] = gui;
}

GuiBase* GuiFrame::GetGuiById(std::string id)
{
    return this->gui_id_map[id];
}
