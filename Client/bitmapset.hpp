#ifndef BITMAPSET_HPP_INCLUDE
#define BITMAPSET_HPP_INCLUDE

#include <vector>

#include "bitmapservice.hpp"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class BitmapSet
{
protected:
    std::vector<ALLEGRO_BITMAP*> bitmaps;

public:
    BitmapSet(int set_size);

    ALLEGRO_BITMAP* GetBitmap(int index) const;
    void SetBitmap(int index, ALLEGRO_BITMAP* bitmap);
};

#endif // BITMAPSET_HPP_INCLUDE
