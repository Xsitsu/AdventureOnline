#ifndef GUIFRAME_HPP_INCLUDE
#define GUIFRAME_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "guiobject.hpp"

#include "color3.hpp"

class GuiFrame : public GuiObject
{
protected:
    virtual void DoDraw() const;

public:
    GuiFrame();
    GuiFrame(Vector2 size);
    GuiFrame(Vector2 size, Vector2 position);
    virtual ~GuiFrame();
};

#endif // GUIFRAME_HPP_INCLUDE
