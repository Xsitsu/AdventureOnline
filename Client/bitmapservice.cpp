#include "bitmapservice.hpp"

#include <iostream>

BitmapService* BitmapService::instance = NULL;

BitmapService::BitmapService()
{
    this->bitmap_sets.resize(this->BITMAPSET_MAX);
    for (int i = 0; i < this->BITMAPSET_MAX; i++)
    {
        this->bitmap_sets[i] = nullptr;
    }
}

void BitmapService::InitBitmapSet(BitmapSets set_id, int set_size)
{
    this->bitmap_sets[set_id] = new BitmapSet(set_size);
}

ALLEGRO_BITMAP* BitmapService::GetBitmap(BitmapSets set_id, int bitmap_id)
{
    if (!this->bitmap_sets[set_id]->IsBitmapLoaded(bitmap_id))
    {
        throw BitmapNotLoadedException();
    }

    return this->bitmap_sets[set_id]->GetBitmap(bitmap_id);;
}

void BitmapService::RegisterBitmap(BitmapSets set_id, int bitmap_id, ALLEGRO_BITMAP* bitmap)
{
    if (this->bitmap_sets[set_id]->IsBitmapLoaded(bitmap_id))
    {
        throw BitmapAlreadyLoadedException();
    }

    this->bitmap_sets[set_id]->SetBitmap(bitmap_id, bitmap);
}

void BitmapService::UnregisterBitmap(BitmapSets set_id, int bitmap_id)
{
    this->GetBitmap(set_id, bitmap_id); // throws exception if not loaded
    this->bitmap_sets[set_id]->SetBitmap(bitmap_id, nullptr);
}

const BitmapSet* BitmapService::GetBitmapSet(BitmapSets set_id) const
{
    return this->bitmap_sets[set_id];
}
