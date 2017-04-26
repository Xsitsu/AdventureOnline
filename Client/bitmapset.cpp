#include "bitmapset.hpp"

BitmapSet::BitmapSet(int set_size)
{
    this->bitmaps.resize(set_size);
}

ALLEGRO_BITMAP* BitmapSet::GetBitmap(int index) const
{
    return this->bitmaps[index];
}

void BitmapSet::SetBitmap(int index, ALLEGRO_BITMAP* bitmap)
{
    this->bitmaps[index] = bitmap;
}
