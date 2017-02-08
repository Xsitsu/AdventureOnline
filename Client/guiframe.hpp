#ifndef GUIFRAME_HPP_INCLUDE
#define GUIFRAME_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "guibase.hpp"

class GuiFrame : public GuiBase
{
protected:
    bool is_filled;
    ALLEGRO_COLOR background_color;

public:
    GuiFrame();
    GuiFrame(Vector2 size);
    GuiFrame(Vector2 size, Vector2 position);
    ~GuiFrame();

    virtual void Draw() const;

    bool GetIsFilled() const;
    void SetIsFilled(bool val);

    ALLEGRO_COLOR GetBackgroundColor() const;
    void SetBackgroundColor(ALLEGRO_COLOR color);

};

#endif // GUIFRAME_HPP_INCLUDE
