#ifndef VECTOR2_HPP_INCLUDE
#define VECTOR2_HPP_INCLUDE

#include <string>

#include "main.h"

struct DLL_EXPORT Vector2
{
    int x;
    int y;

    Vector2()
    {
        this->x = 0;
        this->y = 0;
    }

    Vector2(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2(Vector2& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
    }

    Vector2& operator=(Vector2& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    bool operator==(Vector2& rhs)
    {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    bool operator!=(Vector2& rhs)
    {
        return !(*this == rhs);
    }

    Vector2 operator+(Vector2& rhs)
    {
        return Vector2(this->x + rhs.x, this->y + rhs.y);
    }

    Vector2 operator-(Vector2& rhs)
    {
        return Vector2(this->x - rhs.x, this->y - rhs.y);
    }

    Vector2 operator*(int num)
    {
        return Vector2(this->x * num, this->y * num);
    }

    Vector2 operator/(int num)
    {
        return Vector2(this->x / num, this->y / num);
    }

    std::string ToString()
    {
        return std::string(x) + "/" + y;
    }

};
#endif // VECTOR2_HPP_INCLUDE
