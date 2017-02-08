#ifndef GUIFRAME_HPP_INCLUDE
#define GUIFRAME_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "guibase.hpp"

#include "color3.hpp"

class GuiFrame : public GuiBase
{
protected:
    bool is_filled;
    Color3 background_color;
    unsigned char background_alpha;

    ALLEGRO_COLOR bg_draw_color;

    void UpdateBackgroundDrawColor();

public:
    GuiFrame();
    GuiFrame(Vector2 size);
    GuiFrame(Vector2 size, Vector2 position);
    ~GuiFrame();

    virtual void Draw() const;

    bool GetIsFilled() const;
    void SetIsFilled(bool val);

    Color3 GetBackgroundColor() const;
    void SetBackgroundColor(Color3 color);

    unsigned char GetBackgroundAlpha() const;
    void SetBackgroundAlpha(unsigned char trans);

};

#endif // GUIFRAME_HPP_INCLUDE
