#ifndef RESOURCEFILE_HPP_INCLUDE
#define RESOURCEFILE_HPP_INCLUDE

#include "main.h"

#include "filebase.hpp"
#include "resourcelist.hpp"

class DLL_EXPORT ResourceFile : public FileBase
{
protected:
    ResourceList* DoReadV1();
    void DoWriteV1(ResourceList* rlist);

public:
    ResourceFile();
    ResourceFile(std::string filename);
    ~ResourceFile();

    ResourceList* Read();
    void Write(ResourceList* rlist);
};
#endif // RESOURCEFILE_HPP_INCLUDE
