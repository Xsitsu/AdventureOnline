#ifndef COLOR3_HPP_INCLUDE
#define COLOR3_HPP_INCLUDE

struct Color3
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
    }

    bool operator==(const Color3& rhs)
    {
        return (this->r == rhs.r && this->g == rhs.g && this->b == rhs.b);
    }

};

#endif // COLOR3_HPP_INCLUDE
