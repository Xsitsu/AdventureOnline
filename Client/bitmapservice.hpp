#ifndef BITMAPSERVICE_HPP_INCLUDE
#define BITMAPSERVICE_HPP_INCLUDE

#include <unordered_map>

#include <exception>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class BitmapService
{
protected: // Singleton stuff
    static BitmapService* instance;

    BitmapService() {}
    BitmapService(const BitmapService& copy) {}
    BitmapService& operator=(const BitmapService& rhs) {}
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


protected: // Class stuff
    std::unordered_map<std::string, ALLEGRO_BITMAP*> bitmaps;

public:
    ALLEGRO_BITMAP* GetBitmap(std::string bitmap_name);
    void RegisterBitmap(std::string bitmap_name, ALLEGRO_BITMAP* bitmap);
    void UnregisterBitmap(std::string bitmap_name);

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

