#ifndef GUITEXTBOX_HPP_INCLUDE
#define GUITEXTBOX_HPP_INCLUDE

#include <string>

#include "guiframe.hpp"
#include "color3.hpp"

#include "GameShared/signal.hpp"

#include "allegro5/allegro_font.h"

#include "fontservice.hpp"

//class GuiSelectionService;

#include "guiselectionservice.hpp"

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

    Signal onSelect;
    Signal onDeselect;
    Signal onCharacterType;

    void DoSelect();
    void DoDeselect();
    void DoCharacterType(char c);

    friend class GuiSelectionService;

public:
    SignalListener RegisterOnSelect(signal_callback callback);
    SignalListener RegisterOnDeselect(signal_callback callback);
    SignalListener RegisterOnCharacterType(signal_callback callback);

    void Select();
    void Deselect();

    void AddTextCharacter(char c);
    void DoBackspace();
    void AddCursorPosition(int pos);

};

struct SignalArgsGuiTextBox : SignalArgs
{
    GuiTextBox* text_box;
};

struct SignalArgsGuiTextBoxCharTyped : SignalArgsGuiTextBox
{
    char character;
};

#endif // GUITEXTBOX_HPP_INCLUDE
