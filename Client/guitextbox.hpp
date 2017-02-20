#ifndef GUITEXTBOX_HPP_INCLUDE
#define GUITEXTBOX_HPP_INCLUDE

#include <string>

#include "guiframe.hpp"
#include "color3.hpp"

#include "observer.hpp"

#include "allegro5/allegro_font.h"

#include "fontservice.hpp"

//class GuiSelectionService;

#include "guiselectionservice.hpp"

struct TextBoxSelectionArgs;
struct TextBoxTypingArgs;

class GuiTextBox : public GuiFrame
{
public:
    enum TEXTALIGN {ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER};

protected:
    std::string text;
    TEXTALIGN text_align;

    Color3 text_color;
    unsigned char text_alpha;

    ALLEGRO_COLOR text_draw_color;
    ALLEGRO_FONT* text_draw_font;

    void UpdateTextDrawColor();

    virtual void DoDraw() const;

public:
    GuiTextBox();
    GuiTextBox(Vector2 size);
    GuiTextBox(Vector2 size, Vector2 position);
    virtual ~GuiTextBox();

    std::string GetText() const;
    void SetText(std::string text);

    Color3 GetTextColor() const;
    void SetTextColor(Color3 color);

    unsigned char GetTextAlpha() const;
    void SetTextAlpha(unsigned char trans);

    TEXTALIGN GetTextAlign() const;
    void SetTextAlign(TEXTALIGN align);

    ALLEGRO_FONT* GetTextFont() const;
    void SetTextFont(ALLEGRO_FONT* font);

protected:
    unsigned short cursor_position;
    bool is_selected;

    Observer<TextBoxSelectionArgs*> onSelect;
    Observer<TextBoxSelectionArgs*> onDeselect;
    Observer<TextBoxTypingArgs*> onCharacterType;

    void DoSelect();
    void DoDeselect();
    void DoCharacterType(char c);

    friend class GuiSelectionService;

public:
    void RegisterOnSelect(ListenerBase<TextBoxSelectionArgs*>* listener);
    void RegisterOnDeselect(ListenerBase<TextBoxSelectionArgs*>* listener);
    void RegisterOnCharacterType(ListenerBase<TextBoxTypingArgs*>* listener);

    void Select();
    void Deselect();

    void AddTextCharacter(char c);
    void DoBackspace();
    void AddCursorPosition(int pos);

};

struct TextBoxSelectionArgs
{
    GuiTextBox* text_box;
};

struct TextBoxTypingArgs
{
    GuiTextBox* text_box;
    char character;
};

#endif // GUITEXTBOX_HPP_INCLUDE
