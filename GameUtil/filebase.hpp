#ifndef FILEBASE_HPP_INCLUDE
#define FILEBASE_HPP_INCLUDE

#include <string>
#include <fstream>
#include <exception>

#include "main.h"

class DLL_EXPORT FileBase
{
protected:
    std::string filename;
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
        std::string filename;

    public:
        FileException(std::string filename) : filename(filename) {}
        virtual ~FileException() {}

        virtual const char* what() const noexcept = 0;
    };

    class DLL_EXPORT OpenFailed : public FileException
    {
    protected:

    public:
        OpenFailed(std::string filename) : FileException(filename) {}
        virtual const char* what() const noexcept
        {
            std::string err = "File could not be opened: ";
            err += this->filename;
            err += ".";
            return err.c_str();
        }
    };

    class DLL_EXPORT FileCorrupted : public FileException
    {
    protected:

    public:
        FileCorrupted(std::string filename) : FileException(filename) {}
        virtual const char* what() const noexcept
        {
            std::string err = "File is corrupted: ";
            err += this->filename;
            err += ".";
            return err.c_str();
        }
    };
}
#endif // FILEBASE_HPP_INCLUDE
