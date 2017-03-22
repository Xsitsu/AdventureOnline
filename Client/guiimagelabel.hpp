#ifndef GUIIMAGELABEL_HPP_INCLUDE
#define GUIIMAGELABEL_HPP_INCLUDE

#include "guiframe.hpp"
#include "guiimageelement.hpp"

#include <allegro5/allegro_image.h>

class GuiImageLabel : public GuiFrame, public GuiImageElement
{
protected:
    virtual void DoDraw() const;

public:
    GuiImageLabel();
    GuiImageLabel(Vector2 size);
    GuiImageLabel(Vector2 size, Vector2 position);
    virtual ~GuiImageLabel();
};
#endif // GUIIMAGELABEL_HPP_INCLUDE
