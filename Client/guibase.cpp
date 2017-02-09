#include "guibase.hpp"

GuiBase::GuiBase() : size(Vector2()), position(Vector2()), absolute_position(Vector2()), visible(true)
{}

GuiBase::GuiBase(Vector2 size) : size(size), position(Vector2()), absolute_position(Vector2()), visible(true)
{}

GuiBase::GuiBase(Vector2 size, Vector2 position) : size(size), position(position), absolute_position(position), visible(true)
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
    if (this->parent)
    {
        this->absolute_position = this->parent->GetAbsolutePosition() + this->position;
    }
    else
    {
        this->absolute_position = this->position;
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
        cgui_child_iter iter = this->children.begin();
        cgui_child_iter last = this->children.end();

        for (iter; iter != last; ++iter)
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
    }
}

bool GuiBase::PointIsInBounds(const Vector2& position) const
{
    Vector2 bounds = this->absolute_position + this->size;
    return (this->absolute_position.x <= position.x <= bounds.x) &&
    (this->absolute_position.y <= position.y <= bounds.y);
}
