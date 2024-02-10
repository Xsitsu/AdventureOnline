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
public:
    Database() { this->is_connected = false; }
    virtual ~Database() {}

    bool IsConnected() const { return this->is_connected; }

    virtual void Connect() = 0;
    virtual void Disconnect() = 0;

    virtual void CreateAccount(std::string email, std::string password) = 0;
    virtual Account* ReadAccount(std::string email) = 0;
    virtual void UpdateAccount(Account* account) = 0;
    virtual void DeleteAccount(Account* account) = 0;

    virtual void CreateCharacter(int accID, Character * Character) = 0;
    virtual vector<int> ReadPlayerCharacters (std::string email) = 0;
    virtual Character * ReadCharacterInfo(int) = 0;
    virtual bool CharacterExists(std::string name) = 0;
    virtual void DeleteCharacter(std::string name) = 0;
};

class SQLiteDatabase : public Database
{
protected:
    sqlite3 *db;
    char *zErrMsg;
    int rc;

    void AddCharacterStat(int charID, std::string statname, int statValue);
    int GetStatID(std::string name);

public:
    SQLiteDatabase();
    virtual ~SQLiteDatabase();

    void Connect();
    void Disconnect();

    virtual void CreateAccount(std::string email, std::string password);
    virtual Account* ReadAccount(std::string email);
    virtual void UpdateAccount(Account* account);
    virtual void DeleteAccount(Account* account);

    virtual void CreateCharacter(int accID, Character * Character);
    virtual vector<int> ReadPlayerCharacters (std::string email);
    virtual Character * ReadCharacterInfo(int);
    virtual bool CharacterExists(std::string name);
    virtual void DeleteCharacter(std::string name);
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
