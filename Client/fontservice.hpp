#ifndef FONTSERVICE_HPP_INCLUDE
#define FONTSERVICE_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class FontService
{
protected: // Singleton stuff
    static FontService* instance;

    FontService() {}
    FontService(const FontService& copy) {}
    FontService& operator=(const FontService& rhs) {}
    virtual ~FontService() {}

public:
    static FontService* Instance()
    {
        if (instance == NULL)
        {
            instance = new FontService();
        }
        return instance;
    }


protected: // Class stuff
    ALLEGRO_FONT* font;

public:
    void LoadFonts();
    ALLEGRO_FONT* GetFont();

};

#endif // FONTSERVICE_HPP_INCLUDE
