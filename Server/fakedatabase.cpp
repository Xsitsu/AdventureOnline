#include "database.hpp"

#include <iostream>

FakeDatabase::FakeDatabase() : account_id_counter(0)
{

}

FakeDatabase::~FakeDatabase()
{
    if (this->IsConnected())
    {
        this->Disconnect();
    }
}

void FakeDatabase::Connect()
{
    if (this->IsConnected()) throw DatabaseAlreadyConnectedException();
    this->is_connected = true;
}

void FakeDatabase::Disconnect()
{
    if (!this->IsConnected()) throw DatabaseNotConnectedException();
    this->is_connected = false;
}

void FakeDatabase::CreateAccount(std::string email, std::string password)
{
    if (ReadAccount(email)) throw DatabaseDataAlreadyExistsException();
    this->accounts[email] = new Account(this->account_id_counter++, email, "1", password);
}

Account* FakeDatabase::ReadAccount(std::string email)
{
    Account *account = nullptr;
    try
    {
        account = this->accounts.at(email);
    }
    catch (std::out_of_range &e)
    {}
    return account;
}

void FakeDatabase::UpdateAccount(Account* account)
{
    // if(!ReadAccount(account->GetEmail())) throw DatabaseDataDoesNotExistException();
}

void FakeDatabase::DeleteAccount(Account* account)
{
    if (!ReadAccount(account->GetEmail())) throw DatabaseDataDoesNotExistException();
    this->accounts.erase(account->GetEmail());
}

vector<int> FakeDatabase::ReadPlayerCharacters (std::string email)
{
    vector<int> characters;
    return characters;
}

Character* FakeDatabase::ReadCharacterInfo(int ID)
{
    Character *character= new Character();
    return character;
}

void FakeDatabase::CreateCharacter(int accID, Character * toon)
{

}

bool FakeDatabase::CharacterExists(std::string name)
{
    return false;
}

void FakeDatabase::DeleteCharacter(std::string name)
{

}
