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
