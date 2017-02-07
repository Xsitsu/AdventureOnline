#ifndef GUIBASE_HPP_INCLUDE
#define GUIBASE_HPP_INCLUDE

#include <list>

#include "GameShared/vector2.hpp"

class GuiBase
{
private:
    Vector2 absolute_position;

protected:
    Vector2 size;
    Vector2 position;

    GuiBase* parent;
    std::list<GuiBase*> children;

    void SetParent(GuiBase* parent);

    void UpdateAbsolutePosition();

    GuiBase();
    GuiBase(Vector2 size);
    GuiBase(Vector2 size, Vector2 position);
    ~GuiBase();

public:
    Vector2 GetSize() const;
    Vector2 GetPosition() const;

    void SetSize(const Vector2& size);
    void SetPosition(const Vector2& position);

    void AddChild(GuiBase* child);
    void RemoveChild(GuiBase* child);

    GuiBase* GetParent() const;

    Vector2 GetAbsolutePosition() const;
};

typedef std::list<GuiBase*>::iterator gui_child_iter;

#endif // GUIBASE_HPP_INCLUDE
