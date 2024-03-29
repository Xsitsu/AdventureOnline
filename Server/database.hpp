#ifndef DATABASE_HPP_INCLUDE
#define DATABASE_HPP_INCLUDE
#include <sqlite3.h>
#include <vector>
using std::vector;

#include <exception>

#include "Server/account.hpp"

class Database
{
protected:
    bool is_connected;

    sqlite3 *db;
    char *zErrMsg;
    int rc;

    void AddCharacterStat(int charID, std::string statname, int statValue);
    int GetStatID(std::string name);

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

    void CreateCharacter(int accID, Character * Character);
    vector<int> ReadPlayerCharacters (std::string email);
    Character * ReadCharacterInfo(int);
    bool CharacterExists(std::string name);
    void DeleteCharacter(std::string name);
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

class DatabaseReadException : public DatabaseException
{
protected:

public:

};

class DatabaseDataAlreadyExistsException : public DatabaseException
{
protected:

public:

};

class DatabaseDataDoesNotExistException : public DatabaseException
{
protected:

public:

};

#endif // DATABASE_HPP_INCLUDE
