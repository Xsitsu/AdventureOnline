#ifndef DATABASE_HPP_INCLUDE
#define DATABASE_HPP_INCLUDE

#include <windows.h>
#include <sql.h>
#include <sqlext.h>


#include <exception>

#include "account.hpp"

class Database
{
protected:
    bool is_connected;

    SQLHANDLE h_Environment;
    SQLHANDLE h_DBC;
    SQLHANDLE h_Statement;
    SQLRETURN r_ReturnCode;

public:
    Database();
    ~Database();

    bool IsConnected() const { return this->is_connected; }

    void Connect();
    void Disconnect();

    void CreateAccount(std::string email, std::string password);
    Account* ReadAccount(std::string email);
    void UpdateAccount(Account* account);
    void DeleteAccount(Account* account);
};


// Exception Classes
class DatabaseException : public std::exception
{
protected:

public:
    virtual ~DatabaseException() {}
};

class DatabaseNotConnectedException : public DatabaseException
{
protected:

public:

};

class DatabaseAlreadyConnectedException : public DatabaseException
{
protected:

public:

};

class DatabaseConnectionFailedException : public DatabaseException
{
protected:

public:

};

class DatabaseCreateException : public DatabaseException
{
protected:

public:

};

class DatabaseDataAlreadyExistsException : public DatabaseException
{
protected:

public:

};

class DataDoesNotExistException : public DatabaseException
{
protected:

public:

};

#endif // DATABASE_HPP_INCLUDE
