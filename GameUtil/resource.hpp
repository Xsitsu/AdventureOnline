#ifndef RESOURCE_HPP_INCLUDE
#define RESOURCE_HPP_INCLUDE

#include "main.h"

#include <stdint.h>

struct
#ifdef WINDOWS
DLL_EXPORT
#endif
Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
Resource
{
protected:
    uint32_t width;
    uint32_t height;

    Pixel** pixels;

public:
    Resource(uint32_t width, uint32_t height);
    ~Resource();

    uint32_t GetWidth();
    uint32_t GetHeight();

    Pixel GetPixel(uint32_t width, uint32_t height);
    void SetPixel(uint32_t width, uint32_t height, Pixel pixel);
};
#endif // RESOURCE_HPP_INCLUDE
