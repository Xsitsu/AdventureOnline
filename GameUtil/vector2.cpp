#include "vector2.hpp"

Vector2::Vector2() : x(0), y(0)
{}

Vector2::Vector2(int x, int y) : x(x), y(y)
{}

Vector2::Vector2(const Vector2& rhs) : x(rhs.x), y(rhs.y)
{}

Vector2& Vector2::operator=(const Vector2& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
    return (this->x == rhs.x && this->y == rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
    return !(*this == rhs);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator*(const double num) const
{
    return Vector2((double)this->x * num, (double)this->y * num);
}

Vector2 Vector2::operator/(const double num) const
{
    double dx = this->x;
    double dy = this->y;

    dx = dx / num;
    dy = dy / num;

    return Vector2(dx, dy);
}
