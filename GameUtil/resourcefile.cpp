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

    while (!this->filestream.eof())
    {
        uint32_t width = this->TryRead32();
        uint32_t height = this->TryRead32();

        Resource* resource = new Resource(width, height);
        Pixel pixel;
        for (uint32_t w = 0; w < width; w++)
        {
            for (uint32_t h = 0; h < height; h++)
            {
                try
                {
                    pixel.r = static_cast<char>(this->TryRead8());
                    pixel.g = static_cast<char>(this->TryRead8());
                    pixel.b = static_cast<char>(this->TryRead8());
                    pixel.a = static_cast<char>(this->TryRead8());
                }
                catch(FileException::FileCorrupted& e)
                {
                    delete resource;
                    while (!rlist.empty())
                    {
                        resource = rlist.front();
                        rlist.pop_front();
                        delete resource;
                    }
                    throw e;
                }

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
    this->DoWrite8('A');
    this->DoWrite8('O');
    this->DoWrite8('R');
    this->DoWrite8('F');

    this->DoWrite8(1);

    std::list<Resource*>::iterator iter;
    for (iter = rlist.begin(); iter != rlist.end(); ++iter)
    {
        Resource* resource = *iter;

        uint32_t width = resource->GetWidth();
        uint32_t height = resource->GetHeight();

        this->DoWrite32(width);
        this->DoWrite32(height);

        Pixel pixel;
        for (uint32_t w = 0; w < width; w++)
        {
            for (uint32_t h = 0; h < height; h++)
            {
                pixel = resource->GetPixel(w, h);

                this->DoWrite8(pixel.r);
                this->DoWrite8(pixel.g);
                this->DoWrite8(pixel.b);
                this->DoWrite8(pixel.a);
            }
        }

    }
}
