#include "resourcefile.hpp"

#include <iostream>

ResourceFile::ResourceFile() : FileBase()
{

}

ResourceFile::ResourceFile(std::string filename) : FileBase()
{
    this->Open(filename);
}

ResourceFile::~ResourceFile()
{

}

std::list<Resource*> ResourceFile::Read()
{
    this->filestream.seekg(0, this->filestream.beg);

    char signature[4];
    signature[0] = 'A';
    signature[1] = 'O';
    signature[2] = 'R';
    signature[3] = 'F';

    int version;

    this->CheckHeader(signature, &version);

    try
    {
        if (version == 1)
        {
            return this->DoReadV1();
        }
        else
        {
            throw FileException::FileCorrupted(this->filename);
        }
    }
    catch (std::bad_alloc& e)
    {
        throw FileException::FileCorrupted(this->filename);
    }


}

void ResourceFile::Write(std::list<Resource*> rlist)
{
    this->filestream.seekg(0, this->filestream.beg);

    this->DoWriteV1(rlist);
}


std::list<Resource*> ResourceFile::DoReadV1()
{
    std::list<Resource*> rlist;

    this->filestream.peek(); // Check for EOF

    char buffer[4];
    while (!this->filestream.eof())
    {
        uint32_t width = 0;
        uint32_t height = 0;

        this->filestream.read(buffer, 4);
        width = ((uint8_t)buffer[0] << 24) | ((uint8_t)buffer[1] << 16) | ((uint8_t)buffer[2] << 8) | ((uint8_t)buffer[3] << 0);

        if (this->filestream.fail())
        {
            throw FileException::FileCorrupted(this->filename);
        }

        this->filestream.read(buffer, 4);
        height = ((uint8_t)buffer[0] << 24) | ((uint8_t)buffer[1] << 16) | ((uint8_t)buffer[2] << 8) | ((uint8_t)buffer[3] << 0);

        if (this->filestream.fail())
        {
            throw FileException::FileCorrupted(this->filename);
        }

        Resource* resource = new Resource(width, height);
        Pixel pixel;
        for (uint32_t w = 0; w < width; w++)
        {
            for (uint32_t h = 0; h < height; h++)
            {
                this->filestream.read(buffer, 4);

                if (this->filestream.fail())
                {
                    delete resource;
                    while (!rlist.empty())
                    {
                        resource = rlist.front();
                        rlist.pop_front();
                        delete resource;
                    }
                    throw FileException::FileCorrupted(this->filename);
                }

                pixel.r = buffer[0];
                pixel.g = buffer[1];
                pixel.b = buffer[2];
                pixel.a = buffer[3];

                resource->SetPixel(w, h, pixel);
            }
        }

        rlist.push_back(resource);

        this->filestream.peek();
    }

    return rlist;
}

void ResourceFile::DoWriteV1(std::list<Resource*> rlist)
{
    char buffer[4];
    buffer[0] = 'A';
    buffer[1] = 'O';
    buffer[2] = 'R';
    buffer[3] = 'F';

    this->filestream.write(buffer, 4);

    buffer[0] = 1;

    this->filestream.write(buffer, 1);

    std::list<Resource*>::iterator iter;
    for (iter = rlist.begin(); iter != rlist.end(); ++iter)
    {
        Resource* resource = *iter;

        uint32_t width = resource->GetWidth();
        uint32_t height = resource->GetHeight();

        buffer[0] = (width >> 24) & 255;
        buffer[1] = (width >> 16) & 255;
        buffer[2] = (width >> 8) & 255;
        buffer[3] = (width >> 0) & 255;

        this->filestream.write(buffer, 4);

        buffer[0] = (height >> 24) & 255;
        buffer[1] = (height >> 16) & 255;
        buffer[2] = (height >> 8) & 255;
        buffer[3] = (height >> 0) & 255;

        this->filestream.write(buffer, 4);

        Pixel pixel;
        for (uint32_t w = 0; w < width; w++)
        {
            for (uint32_t h = 0; h < height; h++)
            {
                pixel = resource->GetPixel(w, h);

                buffer[0] = pixel.r;
                buffer[1] = pixel.g;
                buffer[2] = pixel.b;
                buffer[3] = pixel.a;

                this->filestream.write(buffer, 4);
            }
        }

    }
}
