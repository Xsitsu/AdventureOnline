#ifndef GUIIMAGEFRAME_H
#define GUIIMAGEFRAME_H

#include "guiframe.hpp"
#include "allegro5/allegro_image.h"


class GuiImageFrame : public GuiFrame
{
    public:
        GuiImageFrame(ALLEGRO_BITMAP * image = nullptr);
        GuiImageFrame(Vector2 size, ALLEGRO_BITMAP * image = nullptr);
        GuiImageFrame(Vector2 size, Vector2 position, ALLEGRO_BITMAP * image = nullptr);
        virtual ~GuiImageFrame();

        void SetImage(ALLEGRO_BITMAP * val) { b_image = val; }
        ALLEGRO_BITMAP * GetImage() { return b_image; }
        virtual void DoDraw() const;

    protected:
        ALLEGRO_BITMAP * b_image;

    private:
};

#endif // GUIIMAGEFRAME_H
