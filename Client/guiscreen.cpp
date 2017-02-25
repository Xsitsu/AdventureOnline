#include "guiscreen.hpp"

GuiScreen::GuiScreen(GuiBase* base) : base(base)
{
    this->PopulateListFromStructureParse();
}

GuiScreen::~GuiScreen()
{
    while (!this->listeners.empty())
    {
        delete this->listeners.front();
        this->listeners.pop_front();
    }

    delete this->base;
}

void GuiScreen::ParseChild(GuiBase* child)
{
    if (!child) return;

    if (GuiButton* button = dynamic_cast<GuiButton*>(child))
    {
        button->SetScreen(this);
        this->interaction_guis.push_back(button);
    }
    else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(child))
    {
        text_box->SetScreen(this);
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
    bool text_box_selected = false;
    GuiBase* gui = this->FindGuiCoveringPoint(pos);
    if (gui)
    {
        if (GuiButton* button = dynamic_cast<GuiButton*>(gui))
        {
            GuiSelectionService::Instance()->MouseButtonDown(button);
            was_sunk = true;
        }
        else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(gui))
        {
            text_box->Select();
            was_sunk = true;

            text_box_selected = true;
        }
    }

    if (!text_box_selected)
    {
        if (GuiSelectionService::Instance()->TextBoxHasFocus())
        {
            GuiSelectionService::Instance()->SelectTextBox(NULL);
        }
    }
    return was_sunk;
}

bool GuiScreen::HandleMouseUp(const Vector2& pos)
{
    bool was_sunk = false;
    bool did_mouse_up = false;
    GuiBase* gui = this->FindGuiCoveringPoint(pos);
    if (gui)
    {
        if (GuiButton* button = dynamic_cast<GuiButton*>(gui))
        {
            GuiSelectionService::Instance()->MouseButtonUp(button);
            was_sunk = true;

            did_mouse_up = true;
        }
        else if (GuiTextBox* text_box = dynamic_cast<GuiTextBox*>(gui))
        {
            //text_box->Select();
            was_sunk = true;
        }
    }

    if (!did_mouse_up)
        GuiSelectionService::Instance()->LetMouseUp();

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

void GuiScreen::SetGuiId(std::string id, GuiBase* gui)
{
    if (gui != this->base && !gui->HasAncestor(this->base))
    {
        throw "error";
    }

    this->gui_id_map[id] = gui;
}

GuiBase* GuiScreen::GetGuiById(std::string id)
{
    return this->gui_id_map[id];
}

void GuiScreen::RegisterListener(AbstractListener* listener)
{
    this->listeners.push_back(listener);
}
