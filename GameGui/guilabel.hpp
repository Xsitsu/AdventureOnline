#ifndef GUILABEL_HPP_INCLUDE
#define GUILABEL_HPP_INCLUDE

#include "guiobject.hpp"

class DLL_EXPORT GuiLabel : public GuiObject
{
protected:
    virtual void DoDraw() const;

    GuiLabel();
    GuiLabel(Vector2 size);
    GuiLabel(Vector2 size, Vector2 position);
    GuiLabel(const GuiLabel& rhs);
    GuiLabel& operator=(const GuiLabel& rhs);

public:
    virtual ~GuiLabel();
};
#endif // GUILABEL_HPP_INCLUDE
