#ifndef GUISCREEN_HPP_INCLUDE
#define GUISCREEN_HPP_INCLUDE

#include "guibase.hpp"
#include "guibutton.hpp"

#include "GameShared/vector2.hpp"

#include <iostream>

class GuiScreen
{
protected:
    GuiBase* base;
    std::list<GuiButton*> buttons;

    typedef std::list<GuiButton*>::iterator button_iter;

public:
    GuiScreen(GuiBase* base);
    GuiScreen(GuiBase* base, std::list<GuiButton*> buttons);
    ~GuiScreen();

    bool HandleMouseDown(const Vector2& pos);
    bool HandleMouseUp(const Vector2& pos);

    void Draw();
};

#endif // GUISCREEN_HPP_INCLUDE
