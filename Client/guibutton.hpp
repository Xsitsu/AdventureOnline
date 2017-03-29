#ifndef GUIBUTTON_HPP_INCLUDE
#define GUIBUTTON_HPP_INCLUDE

#include "guiobject.hpp"

#include "observer.hpp"

struct GuiButtonArgs;

class GuiButton : public GuiObject
{
protected:
    Observer<GuiButtonArgs*> onClick;
    Observer<GuiButtonArgs*> onMouseDown;
    Observer<GuiButtonArgs*> onMouseUp;
    Observer<GuiButtonArgs*> onMouseEnter;
    Observer<GuiButtonArgs*> onMouseLeave;

    GuiButton();
    GuiButton(Vector2 size);
    GuiButton(Vector2 size, Vector2 position);
    GuiButton(const GuiButton& rhs);
    GuiButton& operator=(const GuiButton& rhs);

public:
    virtual ~GuiButton();

    virtual void DoClick();
    virtual void DoMouseDown();
    virtual void DoMouseUp();
    virtual void DoMouseEnter();
    virtual void DoMouseLeave();

    void RegisterOnClick(ListenerBase<GuiButtonArgs*>* listener);
    void RegisterOnMouseDown(ListenerBase<GuiButtonArgs*>* listener);
    void RegisterOnMouseUp(ListenerBase<GuiButtonArgs*>* listener);
    void RegisterOnMouseEnter(ListenerBase<GuiButtonArgs*>* listener);
    void RegisterOnMouseLeave(ListenerBase<GuiButtonArgs*>* listener);

    void UnregisterOnClick(ListenerBase<GuiButtonArgs*>* listener);
    void UnregisterOnMouseDown(ListenerBase<GuiButtonArgs*>* listener);
    void UnregisterOnMouseUp(ListenerBase<GuiButtonArgs*>* listener);
    void UnregisterOnMouseEnter(ListenerBase<GuiButtonArgs*>* listener);
    void UnregisterOnMouseLeave(ListenerBase<GuiButtonArgs*>* listener);
};

struct GuiButtonArgs
{
    GuiButton* button;
};

#endif // GUIBUTTON_HPP_INCLUDE
