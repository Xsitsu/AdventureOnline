#include "guibase.hpp"

GuiBase::GuiBase() : absolute_position(Vector2()), parent_screen(nullptr), size(Vector2()), position(Vector2()), parent(nullptr), visible(true)
{}

GuiBase::GuiBase(Vector2 size) : absolute_position(Vector2()), parent_screen(nullptr), size(size), position(Vector2()), parent(nullptr), visible(true)
{}

GuiBase::GuiBase(Vector2 size, Vector2 position) : absolute_position(position), parent_screen(nullptr), size(size), position(position),  parent(nullptr), visible(true)
{}

GuiBase::~GuiBase()
{
    while (!this->children.empty())
    {
        delete this->children.front();
        this->children.pop_front();
    }
}

Vector2 GuiBase::GetSize() const
{
    return this->size;
}

Vector2 GuiBase::GetPosition() const
{
    return this->position;
}

bool GuiBase::GetVisible() const
{
    return this->visible;
}

void GuiBase::SetSize(const Vector2& size)
{
    this->size = size;
}

void GuiBase::SetPosition(const Vector2& position)
{
    this->position = position;
    this->UpdateAbsolutePosition();
}

void GuiBase::SetVisible(bool visible)
{
    this->visible = visible;
}

void GuiBase::AddChild(GuiBase* child)
{
    if (child != this && child->GetParent() != this)
    {
        child->SetParent(this);
        this->children.push_back(child);
    }
}

void GuiBase::RemoveChild(GuiBase* child)
{
    if (child != this && child->GetParent() == this)
    {
        child->SetParent(NULL);
        gui_child_iter iter = this->children.begin();
        while (*iter != child)
        {
            ++iter;
        }

        this->children.erase(iter);
    }
}

void GuiBase::SetParent(GuiBase* parent)
{
    this->parent = parent;
    this->UpdateAbsolutePosition();
}

GuiBase* GuiBase::GetParent() const
{
    return this->parent;
}

std::list<GuiBase*> GuiBase::GetChildren() const
{
    return this->children;
}

void GuiBase::UpdateAbsolutePosition()
{
    if (this->parent != NULL)
    {
        this->absolute_position = this->parent->GetAbsolutePosition() + this->position;
    }
    else
    {
        this->absolute_position = this->position;
    }

    if (!this->children.empty())
    {
        gui_child_iter iter;
        for (iter = this->children.begin(); iter != this->children.end(); ++iter)
        {
            GuiBase* gui = *iter;
            gui->UpdateAbsolutePosition();
        }
    }

}

Vector2 GuiBase::GetAbsolutePosition() const
{
    return this->absolute_position;
}

void GuiBase::DrawChildren() const
{
    if (!this->children.empty())
    {
        cgui_child_iter iter;
        for (iter = this->children.begin(); iter != this->children.end(); ++iter)
        {
            (*iter)->Draw();
        }
    }
}

void GuiBase::Draw() const
{
    if (this->visible)
    {
        this->DoDraw();
        this->DrawChildren();
    }
}

bool GuiBase::PointIsInBounds(const Vector2& position) const
{
    Vector2 bounds = this->absolute_position + this->size;

    /*
    std::cout << "Min: " << this->absolute_position.x << "/" << this->absolute_position.y << std::endl;
    std::cout << "Max: " << bounds.x << "/" << bounds.y << std::endl;
    std::cout << "Size: " << this->size.x << "/" << this->size.y << std::endl;
    std::cout << "Check: " << position.x << "/" << position.y << std::endl;
    */
    bool is_in_x_bounds = (this->absolute_position.x <= position.x && position.x <= bounds.x);
    bool is_in_y_bounds = (this->absolute_position.y <= position.y && position.y <= bounds.y);

    /*
    std::cout << "is_in_x_bounds: " << is_in_x_bounds << std::endl;
    std::cout << "is_in_y_bounds: " << is_in_y_bounds << std::endl;
    */
    return is_in_x_bounds && is_in_y_bounds;
}

bool GuiBase::HasAncestor(GuiBase* ancestor) const
{
    GuiBase* parent = this->parent;
    while (parent != nullptr)
    {
        if (parent == ancestor) return true;
        parent = parent->GetParent();
    }
    return false;
}
