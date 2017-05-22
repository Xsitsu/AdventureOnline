#ifndef COLOR3_HPP_INCLUDE
#define COLOR3_HPP_INCLUDE

#include "main.h"

struct
#ifdef WINDOWS
DLL_EXPORT
#endif
Color3
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color3() : r(0), g(0), b(0) {}
    Color3(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
    Color3& operator=(const Color3& rhs)
    {
        this->r = rhs.r;
        this->g = rhs.g;
        this->b = rhs.b;

        return *this;
    }

    bool operator==(const Color3& rhs) const
    {
        return (this->r == rhs.r && this->g == rhs.g && this->b == rhs.b);
    }

};

#endif // COLOR3_HPP_INCLUDE
