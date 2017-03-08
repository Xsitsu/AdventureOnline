#ifndef GUIBASE_HPP_INCLUDE
#define GUIBASE_HPP_INCLUDE

#include <list>
#include <iostream>

#include "vector2.hpp"

class GuiScreen;
class GuiBase
{
private:
    Vector2 absolute_position;
    GuiScreen * parent_screen;

protected:
    Vector2 size;
    Vector2 position;

    GuiBase* parent;
    std::list<GuiBase*> children;

    bool visible;

    void SetParent(GuiBase* parent);

    void UpdateAbsolutePosition();

    void DrawChildren() const;

    virtual void DoDraw() const = 0;

public:
    GuiBase();
    GuiBase(Vector2 size);
    GuiBase(Vector2 size, Vector2 position);
    virtual ~GuiBase();

    Vector2 GetSize() const;
    Vector2 GetPosition() const;
    bool GetVisible() const;

    void SetSize(const Vector2& size);
    void SetPosition(const Vector2& position);
    void SetVisible(bool visible);

    void AddChild(GuiBase* child);
    void RemoveChild(GuiBase* child);

    GuiBase* GetParent() const;
    std::list<GuiBase*> GetChildren() const;

    Vector2 GetAbsolutePosition() const;

    void Draw() const;

    bool PointIsInBounds(const Vector2& position) const;

    bool HasAncestor(GuiBase* ancestor) const;

    GuiScreen * GetScreen() { return parent_screen; }
    void SetScreen(GuiScreen * screen) { parent_screen = screen; }
};

typedef std::list<GuiBase*>::iterator gui_child_iter;
typedef std::list<GuiBase*>::const_iterator cgui_child_iter;

#endif // GUIBASE_HPP_INCLUDE
