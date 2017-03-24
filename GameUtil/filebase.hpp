#ifndef FILEBASE_HPP_INCLUDE
#define FILEBASE_HPP_INCLUDE

#include <string>
#include <fstream>
#include <exception>

#include "main.h"

class DLL_EXPORT FileBase
{
protected:
    std::fstream filestream;

    void CheckHeader(char* signature, int* version);

    virtual std::string GetExtension() = 0;

public:
    FileBase();
    FileBase(std::string filename);
    virtual ~FileBase();

    void Open(std::string filename);
    void Close();
    void Create(std::string filename);
    bool IsOpen();
};

namespace FileException
{
    class DLL_EXPORT FileException : public std::exception
    {
    protected:

    public:
        virtual ~FileException() {}
    };

    class DLL_EXPORT OpenFailed : public FileException
    {
    protected:

    public:

    };

    class DLL_EXPORT FileCorrupted : public FileException
    {
    protected:

    public:

    };
}
#endif // FILEBASE_HPP_INCLUDE
