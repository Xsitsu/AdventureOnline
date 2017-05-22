#ifndef GUIIMAGEELEMENT_HPP_INCLUDE
#define GUIIMAGEELEMENT_HPP_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "color3.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
GuiImageElement
{
protected:
    ALLEGRO_BITMAP* image;
    Color3 image_tint;
    unsigned char image_alpha;

    ALLEGRO_COLOR tint_draw_color;

    void UpdateTintDrawColor();

public:
    GuiImageElement();
    ~GuiImageElement();

    void SetImage(ALLEGRO_BITMAP* image);
    ALLEGRO_BITMAP* GetImage() const;

    void SetImageTint(const Color3& image_tint);
    Color3 GetImageTint() const;

    void SetImageAlpha(unsigned char alpha);
    unsigned char GetImageAlpha() const;
};

#endif // GUIIMAGEELEMENT_HPP_INCLUDE
