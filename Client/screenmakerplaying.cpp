#include "screenmaker.hpp"

GuiScreen* ScreenMakerPlaying::MakeScreen()
{
    GuiFrame* base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundAlpha(0);

    GuiScreen* screen = new GuiScreen(base_frame);

    return screen;
}
