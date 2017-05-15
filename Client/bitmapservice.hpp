#ifndef BITMAPSERVICE_HPP_INCLUDE
#define BITMAPSERVICE_HPP_INCLUDE

#include <exception>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class BitmapSet;

#include "bitmapset.hpp"

class BitmapService
{
protected: // Singleton stuff
    static BitmapService* instance;

    BitmapService();
    BitmapService(const BitmapService& copy) {}
    BitmapService& operator=(const BitmapService& rhs) { return *this; }
    virtual ~BitmapService() {}

public:
    static BitmapService* Instance()
    {
        if (instance == NULL)
        {
            instance = new BitmapService();
        }
        return instance;
    }


public: // Class stuff
    enum BitmapSets {
        BITMAPSET_BACKGROUND,
        BITMAPSET_TILE,
        BITMAPSET_CHARACTER,
        BITMAPSET_GUI_ELEMENT,
        BITMAPSET_HAIR_FEMALE,
        BITMAPSET_HAIR_MALE,

        BITMAPSET_MAX
    };

protected:
    std::vector<BitmapSet*> bitmap_sets;

public:
    void InitBitmapSet(BitmapSets set_id, int set_size);

    ALLEGRO_BITMAP* GetBitmap(BitmapSets set_id, int bitmap_id);
    void RegisterBitmap(BitmapSets set_id, int bitmap_id, ALLEGRO_BITMAP* bitmap);
    void UnregisterBitmap(BitmapSets set_id, int bitmap_id);

    const BitmapSet* GetBitmapSet(BitmapSets set_id) const;
};

class BitmapServiceException : public std::exception
{
protected:

public:

};

class BitmapNotLoadedException : public BitmapServiceException
{
protected:

public:

};

class BitmapAlreadyLoadedException : public BitmapServiceException
{
protected:

public:

};

#endif // BITMAPSERVICE_HPP_INCLUDE

