#ifndef GUITEXTLABEL_HPP_INCLUDE
#define GUITEXTLABEL_HPP_INCLUDE

#include "guilabel.hpp"
#include "guitextelement.hpp"

class GuiTextLabel : public GuiLabel, public GuiTextElement
{
protected:
    virtual void DoDraw() const;

public:
    GuiTextLabel();
    GuiTextLabel(Vector2 size);
    GuiTextLabel(Vector2 size, Vector2 position);
    virtual ~GuiTextLabel();
};

#endif // GUITEXTLABEL_HPP_INCLUDE
