#ifndef GUIBUTTON_HPP_INCLUDE
#define GUIBUTTON_HPP_INCLUDE

#include "guiframe.hpp"

#include "GameShared/signal.hpp"

class GuiButton : public GuiFrame
{
protected:
    Signal onClick;
    Signal onMouseEnter;
    Signal onMouseLeave;

public:
    GuiButton();
    GuiButton(Vector2 size);
    GuiButton(Vector2 size, Vector2 position);
    virtual ~GuiButton();

    void DoClick();
    void DoMouseEnter();
    void DoMouseLeave();

    SignalListener RegisterOnClick(signal_callback callback);
    SignalListener RegisterOnMouseEnter(signal_callback callback);
    SignalListener RegisterOnMouseLeave(signal_callback callback);
};

#endif // GUIBUTTON_HPP_INCLUDE
