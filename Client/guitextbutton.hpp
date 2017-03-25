#ifndef GUITEXTBUTTON_HPP_INCLUDE
#define GUITEXTBUTTON_HPP_INCLUDE

#include "guibutton.hpp"
#include "guitextelement.hpp"

class GuiTextButton : public GuiButton, public GuiTextElement
{
protected:
    virtual void DoDraw() const;

public:
    GuiTextButton();
    GuiTextButton(Vector2 size);
    GuiTextButton(Vector2 size, Vector2 position);
    virtual ~GuiTextButton();

    virtual void DoClick();
    virtual void DoMouseDown();
    virtual void DoMouseUp();
    virtual void DoMouseEnter();
    virtual void DoMouseLeave();

};

#endif // GUITEXTBUTTON_HPP_INCLUDE
