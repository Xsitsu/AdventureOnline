#ifndef FILEBASE_HPP_INCLUDE
#define FILEBASE_HPP_INCLUDE

#include <string>
#include <fstream>
#include <exception>

#include "main.h"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
FileBase
{
protected:
    char readbuffer[4];

    std::string filename;
    std::fstream filestream;

    void CheckHeader(char* signature, int* version);

    virtual std::string GetExtension() = 0;

    uint8_t TryRead8();
    uint16_t TryRead16();
    uint32_t TryRead32();

    void DoWrite8(uint8_t data);
    void DoWrite16(uint16_t data);
    void DoWrite32(uint32_t data);

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
    class
#ifdef WINDOWS
DLL_EXPORT
#endif
    FileException : public std::exception
    {
    protected:
        std::string filename;

    public:
        FileException(std::string filename) : filename(filename) {}
        virtual ~FileException() {}

        virtual const char* what() const noexcept = 0;
    };

    class
#ifdef WINDOWS
DLL_EXPORT
#endif
    OpenFailed : public FileException
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

    class
#ifdef WINDOWS
DLL_EXPORT
#endif
    FileCorrupted : public FileException
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

    class
#ifdef WINDOWS
DLL_EXPORT
#endif
    InvalidFileVersion : public FileException
    {
    protected:
        int version;

    public:
        InvalidFileVersion(std::string filename, int version) : FileException(filename), version(version) {}
        virtual const char* what() const noexcept
        {
            std::string err = "Incorrect file version in file: ";
            err += this->filename;
            err += " with V";
            err += this->version;
            err += ".";
            return err.c_str();
        }
    };
}
#endif // FILEBASE_HPP_INCLUDE
