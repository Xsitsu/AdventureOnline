#ifndef VECTOR2_HPP_INCLUDE
#define VECTOR2_HPP_INCLUDE

#include <string>

#include "main.h"

struct DLL_EXPORT Vector2
{
    int x;
    int y;

    Vector2() : x(0), y(0) {}

    Vector2(int x, int y) : x(x), y(y) {}

    Vector2(const Vector2& rhs) : x(rhs.x), y(rhs.y) {}

    Vector2& operator=(const Vector2& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    bool operator==(const Vector2& rhs) const
    {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    bool operator!=(const Vector2& rhs) const
    {
        return !(*this == rhs);
    }

    Vector2 operator+(const Vector2& rhs) const
    {
        return Vector2(this->x + rhs.x, this->y + rhs.y);
    }

    Vector2 operator-(const Vector2& rhs) const
    {
        return Vector2(this->x - rhs.x, this->y - rhs.y);
    }

    Vector2 operator*(const int num) const
    {
        return Vector2(this->x * num, this->y * num);
    }

    Vector2 operator/(const int num) const
    {
        return Vector2(this->x / num, this->y / num);
    }

};
#endif // VECTOR2_HPP_INCLUDE
