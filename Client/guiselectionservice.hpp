#ifndef GUISELECTIONSERVICE_HPP_INCLUDE
#define GUISELECTIONSERVICE_HPP_INCLUDE

class GuiTextBox;

#include "allegro5/allegro.h"

#include "guibase.hpp"
#include "guibutton.hpp"
#include "guitextbox.hpp"
#include "GameShared/vector2.hpp"

class GuiSelectionService
{
protected: // Singleton stuff
    static GuiSelectionService* instance;

    GuiSelectionService();
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

    GuiButton* current_button_down;

    char lowercase_keys[ALLEGRO_KEY_MAX];
    char uppercase_keys[ALLEGRO_KEY_MAX];

    void InitKeyList();
    void SetKey(int index, char lower, char upper);

    bool CheckModifier(unsigned int modifiers, int modifier);
    char AllegroKeycodeToAscii(int keycode, unsigned int modifiers);

public:
    GuiTextBox* GetSelectedTextBox();
    void SelectTextBox(GuiTextBox* text_box);

    GuiBase* GetCurrentMouseHover();
    void SetCurrentMouseHover(GuiBase* hover);

    bool TextBoxHasFocus();
    void HandleKeyboardTyping(ALLEGRO_KEYBOARD_EVENT keyboard);

    void MouseButtonDown(GuiButton* button);
    void MouseButtonUp(GuiButton* button);
    void LetMouseUp();

    void HandleCurrentScreenChanged();
};

#endif // GUISELECTIONSERVICE_HPP_INCLUDE
