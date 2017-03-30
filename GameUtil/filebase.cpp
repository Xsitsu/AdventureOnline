#include "filebase.hpp"

FileBase::FileBase()
{

}

FileBase::FileBase(std::string filename)
{
    this->Open(filename);
}

FileBase::~FileBase()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

void FileBase::Open(std::string filename)
{
    if (!this->IsOpen())
    {
        this->filestream.open(filename + this->GetExtension(), std::fstream::in | std::fstream::out | std::fstream::binary);

        if (!this->IsOpen())
        {
            throw FileException::OpenFailed(filename);
        }

        this->filename = filename;
    }
}

void FileBase::Close()
{
    if (this->IsOpen())
    {
        this->filestream.close();
    }
}

void FileBase::Create(std::string filename)
{
    if (!this->IsOpen())
    {
        this->filestream.open(filename + this->GetExtension(), std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

        if (!this->IsOpen())
        {
            throw FileException::OpenFailed(filename);
        }

        this->filename = filename;
    }
}

bool FileBase::IsOpen()
{
    return this->filestream.is_open();
}

void FileBase::CheckHeader(char* signature, int* version)
{
    char buffer[4];
    this->filestream.read(buffer, 4);

    if (buffer[0] != signature[0] || buffer[1] != signature[1] ||
        buffer[2] != signature[2] || buffer[3] != signature[3])
    {
        throw FileException::FileCorrupted(this->filename);
    }

    if (this->filestream.eof())
    {
        throw FileException::FileCorrupted(this->filename);
    }

    this->filestream.read(buffer, 1);
    *version = buffer[0];

    if (this->filestream.eof())
    {
        throw FileException::FileCorrupted(this->filename);
    }
}

uint8_t FileBase::TryRead8()
{
    this->filestream.read(this->readbuffer, 1);
    if (this->filestream.fail())
    {
        throw FileException::FileCorrupted(this->filename);
    }

    return (uint8_t)this->readbuffer[0];
}

uint16_t FileBase::TryRead16()
{
    this->filestream.read(this->readbuffer, 2);
    if (this->filestream.fail())
    {
        throw FileException::FileCorrupted(this->filename);
    }

    uint8_t ret;
    ret = (uint8_t)this->readbuffer[0] << 8 | (uint8_t)this->readbuffer[1];
    return ret;
}

uint32_t FileBase::TryRead32()
{
    this->filestream.read(this->readbuffer, 4);
    if (this->filestream.fail())
    {
        throw FileException::FileCorrupted(this->filename);
    }

    uint32_t ret;
    ret = (uint8_t)this->readbuffer[0] << 24 | (uint8_t)this->readbuffer[1] << 16 | (uint8_t)this->readbuffer[2] << 8 | (uint8_t)this->readbuffer[3];
    return ret;
}


void FileBase::DoWrite8(uint8_t data)
{
    this->readbuffer[0] = data;

    this->filestream.write(this->readbuffer, 1);
}

void FileBase::DoWrite16(uint16_t data)
{
    this->readbuffer[0] = (data >> 8) & 255;
    this->readbuffer[1] = (data >> 0) & 255;

    this->filestream.write(this->readbuffer, 2);
}

void FileBase::DoWrite32(uint32_t data)
{
    this->readbuffer[0] = (data >> 24) & 255;
    this->readbuffer[1] = (data >> 16) & 255;
    this->readbuffer[2] = (data >> 8) & 255;
    this->readbuffer[3] = (data >> 0) & 255;

    this->filestream.write(this->readbuffer, 4);
}
