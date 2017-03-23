#include "resourcefile.hpp"

ResourceFile::ResourceFile() : FileBase()
{

}

ResourceFile::ResourceFile(std::string filename) : FileBase()
{
    filename += ".aorf";
    this->Open(filename);
}

ResourceFile::~ResourceFile()
{

}

ResourceList* ResourceFile::Read()
{
    this->filestream.seekg(0, this->filestream.beg);

    char signature[4];
    signature[0] = 'A';
    signature[1] = 'O';
    signature[2] = 'R';
    signature[3] = 'F';

    int version;

    this->CheckHeader(signature, &version);

    if (version == 1)
    {
        return this->DoReadV1();
    }
    else
    {
        throw FileException::FileCorrupted();
    }
}

void ResourceFile::Write(ResourceList* rlist)
{
    this->filestream.seekg(0, this->filestream.beg);

    this->DoWriteV1(rlist);
}


ResourceList* ResourceFile::DoReadV1()
{
    return nullptr;
}

void ResourceFile::DoWriteV1(ResourceList* rlist)
{

}
