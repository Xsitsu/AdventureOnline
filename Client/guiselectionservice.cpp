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
