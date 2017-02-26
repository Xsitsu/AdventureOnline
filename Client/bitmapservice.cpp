#include "bitmapservice.hpp"

#include <iostream>

BitmapService* BitmapService::instance = NULL;

ALLEGRO_BITMAP* BitmapService::GetBitmap(std::string bitmap_name)
{
    ALLEGRO_BITMAP* bitmap = this->bitmaps[bitmap_name];
    if (!bitmap) throw BitmapNotLoadedException();
    return bitmap;
}

void BitmapService::RegisterBitmap(std::string bitmap_name, ALLEGRO_BITMAP* bitmap)
{
    if (this->bitmaps[bitmap_name]) throw BitmapAlreadyLoadedException();
    this->bitmaps[bitmap_name] = bitmap;
}

void BitmapService::UnregisterBitmap(std::string bitmap_name)
{
    this->GetBitmap(bitmap_name); // throws exception if not loaded
    this->bitmaps.erase(bitmap_name);
}
