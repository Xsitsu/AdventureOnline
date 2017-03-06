#include "screenmaker.hpp"

GuiScreen* ScreenMakerEmpty::MakeScreen()
{
    GuiFrame* base = new GuiFrame(Vector2(0, 0), Vector2(0, 0));
    base->SetBackgroundAlpha(0);
    return new GuiScreen(base);
}
