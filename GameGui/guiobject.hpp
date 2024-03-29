#ifndef GUIOBJECT_HPP_INCLUDE
#define GUIOBJECT_HPP_INCLUDE

#include "guibase.hpp"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "color3.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
GuiObject : public GuiBase
{
protected:
    bool is_filled;
    Color3 background_color;
    unsigned char background_alpha;
    Vector2 rounding;

    ALLEGRO_COLOR bg_draw_color;

    void UpdateBackgroundDrawColor();

    virtual void DoDraw() const;

    GuiObject();
    GuiObject(Vector2 size);
    GuiObject(Vector2 size, Vector2 position);
    GuiObject(const GuiObject& rhs);
    GuiObject& operator=(const GuiObject& rhs);

public:

    virtual ~GuiObject();

    bool GetIsFilled() const;
    void SetIsFilled(bool val);

    Color3 GetBackgroundColor() const;
    void SetBackgroundColor(Color3 color);

    unsigned char GetBackgroundAlpha() const;
    void SetBackgroundAlpha(unsigned char alpha);

    Vector2 GetRounding() const;
    void SetRounding(Vector2 rounding);

};

#endif // GUIOBJECT_HPP_INCLUDE
