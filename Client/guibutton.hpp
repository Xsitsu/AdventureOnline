#ifndef GUIBUTTON_HPP_INCLUDE
#define GUIBUTTON_HPP_INCLUDE

#include "guiframe.hpp"

class GuiButton : public GuiFrame
{
protected:

public:
    GuiButton();
    GuiButton(Vector2 size);
    GuiButton(Vector2 size, Vector2 position);
    virtual ~GuiButton();

    void DoClick();

};

#endif // GUIBUTTON_HPP_INCLUDE
