#ifndef RESOURCEFILE_HPP_INCLUDE
#define RESOURCEFILE_HPP_INCLUDE

#include "main.h"

#include <list>

#include "filebase.hpp"
#include "resource.hpp"

class DLL_EXPORT ResourceFile : public FileBase
{
protected:
    std::list<Resource*> DoReadV1();
    void DoWriteV1(std::list<Resource*> rlist);

    virtual std::string GetExtension() { return ".aorf"; }

public:
    ResourceFile();
    ResourceFile(std::string filename);
    ~ResourceFile();

    std::list<Resource*> Read();
    void Write(std::list<Resource*> rlist);
};
#endif // RESOURCEFILE_HPP_INCLUDE
