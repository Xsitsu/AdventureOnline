#include "guiscreen.hpp"

GuiScreen::GuiScreen(GuiBase* base) : base(base)
{
    this->PopulateListFromStructureParse();
}

GuiScreen::~GuiScreen()
{
    delete this->base;
}

void GuiScreen::ParseChild(GuiBase* child)
{
    if (!child) return;

    if (GuiButton* button = dynamic_cast<GuiButton*>(child))
    {
        this->interaction_guis.push_back(button);
    }
    else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(child))
    {
        this->interaction_guis.push_back(text_box);
    }

    std::list<GuiBase*> children = child->GetChildren();
    gui_child_iter iter = children.begin();
    for (iter; iter != children.end(); ++iter)
    {
        this->ParseChild(*iter);
    }
}

void GuiScreen::PopulateListFromStructureParse()
{
    this->interaction_guis.clear();

    this->ParseChild(this->base);
}


void GuiScreen::Draw()
{
    this->base->Draw();
}

void GuiScreen::RemoveInteractionGui(GuiBase* gui)
{
    gui_child_iter iter = this->interaction_guis.begin();
    while (iter != this->interaction_guis.end())
    {
        GuiBase* current = *iter;
        if (current == gui)
        {
            this->interaction_guis.erase(iter);
            return;
        }

        ++iter;
    }
}

GuiBase* GuiScreen::FindGuiCoveringPoint(const Vector2& pos)
{
    GuiBase* gui = NULL;
    gui_child_iter iter = this->interaction_guis.begin();
    while (iter != this->interaction_guis.end())
    {
        gui = *iter;
        if (!gui)
        {
            this->RemoveInteractionGui(gui);
        }
        else if (!gui->HasAncestor(this->base))
        {
            this->RemoveInteractionGui(gui);
        }
        else if (gui->GetVisible() && gui->PointIsInBounds(pos))
        {
            return gui;
        }

        ++iter;
    }

    return NULL;
}

bool GuiScreen::HandleMouseDown(const Vector2& pos)
{
    bool was_sunk = false;
    GuiBase* gui = this->FindGuiCoveringPoint(pos);
    if (gui)
    {
        if (GuiButton* button = dynamic_cast<GuiButton*>(gui))
        {
            button->DoClick();
            was_sunk = true;
        }
        else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(gui))
        {
            text_box->Select();
            was_sunk = true;
        }
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseUp(const Vector2& pos)
{
    bool was_sunk = false;
    GuiBase* gui = this->FindGuiCoveringPoint(pos);
    if (gui)
    {
        if (GuiButton* button = dynamic_cast<GuiButton*>(gui))
        {
            //button->DoClick();
            was_sunk = true;
        }
        else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(gui))
        {
            //text_box->Select();
            was_sunk = true;
        }
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseMove(const Vector2& pos)
{
    bool was_sunk = false;
    GuiBase* gui = this->FindGuiCoveringPoint(pos);

    GuiSelectionService* service = GuiSelectionService::Instance();
    GuiBase* cur_hover = service->GetCurrentMouseHover();

    if (gui != cur_hover)
    {
        if (cur_hover)
        {
            if (GuiButton* button = dynamic_cast<GuiButton*>(cur_hover))
            {
                button->DoMouseLeave();
                was_sunk = true;
            }
            else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(cur_hover))
            {
                //text_box->Select();
                was_sunk = true;
            }
        }

        service->SetCurrentMouseHover(gui);

        if (gui)
        {
            if (GuiButton* button = dynamic_cast<GuiButton*>(gui))
            {
                button->DoMouseEnter();
                was_sunk = true;
            }
            else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(gui))
            {
                //text_box->Select();
                was_sunk = true;
            }
        }
    }

    return was_sunk;
}
