#ifndef GUIBUTTON_HPP_INCLUDE
#define GUIBUTTON_HPP_INCLUDE

#include "guiframe.hpp"

#include "GameShared/signal.hpp"

class GuiButton : public GuiFrame
{
protected:
    Signal onClick;
    Signal onMouseDown;
    Signal onMouseUp;
    Signal onMouseEnter;
    Signal onMouseLeave;

public:
    GuiButton();
    GuiButton(Vector2 size);
    GuiButton(Vector2 size, Vector2 position);
    virtual ~GuiButton();

    virtual void DoClick();
    virtual void DoMouseDown();
    virtual void DoMouseUp();
    virtual void DoMouseEnter();
    virtual void DoMouseLeave();

    SignalListener RegisterOnClick(signal_callback callback);
    SignalListener RegisterOnMouseDown(signal_callback callback);
    SignalListener RegisterOnMouseUp(signal_callback callback);
    SignalListener RegisterOnMouseEnter(signal_callback callback);
    SignalListener RegisterOnMouseLeave(signal_callback callback);
};

struct SignalArgsGuiButton : SignalArgs
{
    GuiButton* button;
};

#endif // GUIBUTTON_HPP_INCLUDE
