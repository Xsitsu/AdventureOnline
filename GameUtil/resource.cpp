#include "resource.hpp"

Resource::Resource(uint32_t width, uint32_t height) : width(width), height(height)
{
    this->pixels = new Pixel*[width];
    for (uint32_t i = 0; i < width; i++)
    {
        this->pixels[i] = new Pixel[height];
    }
}

Resource::~Resource()
{
    for (unsigned int i = 0; i < this->width; i++)
    {
        delete[] this->pixels[i];
    }
    delete[] this->pixels;
}

uint32_t Resource::GetWidth()
{
    return this->width;
}

uint32_t Resource::GetHeight()
{
    return this->height;
}

Pixel Resource::GetPixel(uint32_t width, uint32_t height)
{
    return this->pixels[width][height];
}

void Resource::SetPixel(uint32_t width, uint32_t height, Pixel pixel)
{
    this->pixels[width][height] = pixel;
}
