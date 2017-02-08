#ifndef COLOR3_HPP_INCLUDE
#define COLOR3_HPP_INCLUDE

struct Color3
{
    unsigned char x;
    unsigned char y;
    unsigned char z;

    Color3() : x(0), y(0), z(0) {}
    Color3(unsigned char x, unsigned char y, unsigned char z) : x(x), y(y), z(z) {}
    Color3& operator=(const Color3& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }

    bool operator==(const Color3& rhs)
    {
        return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
    }



};

#endif // COLOR3_HPP_INCLUDE
