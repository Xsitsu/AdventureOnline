#ifndef GUIIMAGEBUTTON_HPP_INCLUDE
#define GUIIMAGEBUTTON_HPP_INCLUDE

#include "gui_dll_export.h"

#include "guibutton.hpp"
#include "guiimageelement.hpp"

class DLL_EXPORT GuiImageButton : public GuiButton, public GuiImageElement
{
protected:
    virtual void DoDraw() const;

public:
    GuiImageButton();
    GuiImageButton(Vector2 size);
    GuiImageButton(Vector2 size, Vector2 position);
    virtual ~GuiImageButton();

    virtual void DoClick();
    virtual void DoMouseDown();
    virtual void DoMouseUp();
    virtual void DoMouseEnter();
    virtual void DoMouseLeave();
};
#endif // GUIIMAGEBUTTON_HPP_INCLUDE
