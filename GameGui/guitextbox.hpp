#ifndef GUITEXTBOX_HPP_INCLUDE
#define GUITEXTBOX_HPP_INCLUDE

#include "guiobject.hpp"
#include "guitextelement.hpp"

#include "observer.hpp"

#include "guiselectionservice.hpp"

struct
#ifdef WINDOWS
DLL_EXPORT
#endif
TextBoxSelectionArgs;
struct
#ifdef WINDOWS
DLL_EXPORT
#endif
TextBoxTypingArgs;

class
#ifdef WINDOWS
DLL_EXPORT
#endif
GuiTextBox : public GuiObject, public GuiTextElement
{
    friend class GuiSelectionService;

protected:
    virtual void DoDraw() const;

    unsigned short cursor_position;
    bool is_selected;
    int text_width;
    int cursor_text_width;

    Observer<TextBoxSelectionArgs*> onSelect;
    Observer<TextBoxSelectionArgs*> onDeselect;
    Observer<TextBoxTypingArgs*> onCharacterType;

    void DoSelect();
    void DoDeselect();
    void DoCharacterType(char c);

    virtual void UpdateTextWidth();
    virtual void UpdateCursorTextWidth();

public:
    GuiTextBox();
    GuiTextBox(Vector2 size);
    GuiTextBox(Vector2 size, Vector2 position);
    virtual ~GuiTextBox();

    virtual void SetText(std::string text);
    virtual void SetTextFont(ALLEGRO_FONT* font);

    void RegisterOnSelect(ListenerBase<TextBoxSelectionArgs*>* listener);
    void RegisterOnDeselect(ListenerBase<TextBoxSelectionArgs*>* listener);
    void RegisterOnCharacterType(ListenerBase<TextBoxTypingArgs*>* listener);

    void Select();
    void Deselect();

    void AddTextCharacter(char c);
    void DoBackspace();
    void AddCursorPosition(int pos);
    void SetCursorPosition(int pos);

};

struct
#ifdef WINDOWS
DLL_EXPORT
#endif
TextBoxSelectionArgs
{
    GuiTextBox* text_box;
};

struct
#ifdef WINDOWS
DLL_EXPORT
#endif
TextBoxTypingArgs
{
    GuiTextBox* text_box;
    char character;
};

#endif // GUITEXTBOX_HPP_INCLUDE
