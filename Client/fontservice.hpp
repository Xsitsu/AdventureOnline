#ifndef FONTSERVICE_HPP_INCLUDE
#define FONTSERVICE_HPP_INCLUDE

#include <unordered_map>

#include <exception>
#include <string>

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class FontService
{
protected: // Singleton stuff
    static FontService* instance;

    FontService() {}
    FontService(const FontService& copy) {}
    FontService& operator=(const FontService& rhs) { return *this; }
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
    std::unordered_map<std::string, ALLEGRO_FONT*> fonts;

public:
    ALLEGRO_FONT* GetFont(std::string font_name);
    void RegisterFont(std::string font_name, ALLEGRO_FONT* font);
    void UnregisterFont(std::string font_name);

    static std::string FONT_PATH;
    static std::string DEBUG_FONT;
};

class FontServiceException : public std::exception
{
protected:

public:

};

class FontNotLoadedException : public FontServiceException
{
protected:

public:

};

class FontAlreadyLoadedException : public FontServiceException
{
protected:

public:

};

#endif // FONTSERVICE_HPP_INCLUDE
