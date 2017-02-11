#ifndef GUISELECTIONSERVICE_HPP_INCLUDE
#define GUISELECTIONSERVICE_HPP_INCLUDE

class GuiTextBox;

#include "allegro5/allegro.h"

#include "guibase.hpp"
#include "guitextbox.hpp"
#include "GameShared/vector2.hpp"

class GuiSelectionService
{
protected: // Singleton stuff
    static GuiSelectionService* instance;

    GuiSelectionService() : selected_text_box(NULL), current_mouse_hover(NULL) {}
    GuiSelectionService(const GuiSelectionService& copy) {}
    GuiSelectionService& operator=(const GuiSelectionService& rhs) {}
    virtual ~GuiSelectionService() {}

public:
    static GuiSelectionService* Instance()
    {
        if (instance == NULL)
        {
            instance = new GuiSelectionService();
        }
        return instance;
    }


protected: // Class stuff
    GuiTextBox* selected_text_box;
    GuiBase* current_mouse_hover;

public:
    GuiTextBox* GetSelectedTextBox();
    void SelectTextBox(GuiTextBox* text_box);

    GuiBase* GetCurrentMouseHover();
    void SetCurrentMouseHover(GuiBase* hover);

    void HandleKeyboardTyping(ALLEGRO_KEYBOARD_EVENT keyboard);

};

#endif // GUISELECTIONSERVICE_HPP_INCLUDE
