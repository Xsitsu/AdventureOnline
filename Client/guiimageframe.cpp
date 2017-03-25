#include "guiimageframe.hpp"

GuiImageFrame::GuiImageFrame(ALLEGRO_BITMAP * image): b_image(image), GuiFrame()
{

}
GuiImageFrame::GuiImageFrame(Vector2 size, ALLEGRO_BITMAP * image): b_image(image), GuiFrame(size){}
GuiImageFrame::GuiImageFrame(Vector2 size, Vector2 position, ALLEGRO_BITMAP * image ): b_image(image), GuiFrame(size, position){}

GuiImageFrame::~GuiImageFrame()
{
    al_destroy_bitmap(b_image);
}

void GuiImageFrame::DoDraw() const
{
    Vector2 draw_pos = GetAbsolutePosition();
    GuiFrame::DoDraw();
    al_draw_bitmap(b_image,draw_pos.x, draw_pos.y,0);

    //dtor
}
