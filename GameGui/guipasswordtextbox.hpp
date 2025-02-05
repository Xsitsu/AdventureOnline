#ifndef GUIPASSWORDTEXTBOX_HPP_INCLUDE
#define GUIPASSWORDTEXTBOX_HPP_INCLUDE

#include "guitextbox.hpp"

class DLL_EXPORT GuiPasswordTextBox : public GuiTextBox
{
    friend class GuiSelectionService;

protected:
    virtual void DoDraw() const;

    virtual void UpdateTextWidth();
    virtual void UpdateCursorTextWidth();

    std::string draw_text;

public:
    GuiPasswordTextBox();
    GuiPasswordTextBox(Vector2 size);
    GuiPasswordTextBox(Vector2 size, Vector2 position);
    virtual ~GuiPasswordTextBox();

};

#endif // GUIPASSWORDTEXTBOX_HPP_INCLUDE
