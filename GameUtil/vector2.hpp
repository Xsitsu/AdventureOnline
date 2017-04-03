#ifndef VECTOR2_HPP_INCLUDE
#define VECTOR2_HPP_INCLUDE

#include "main.h"

struct DLL_EXPORT Vector2
{
    int x;
    int y;

    Vector2();
    Vector2(int x, int y);
    Vector2(const Vector2& rhs);
    Vector2& operator=(const Vector2& rhs);

    bool operator==(const Vector2& rhs) const;
    bool operator!=(const Vector2& rhs) const;
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(const double num) const;
    Vector2 operator/(const double num) const;

};
#endif // VECTOR2_HPP_INCLUDE
