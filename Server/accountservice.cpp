#include "accountservice.hpp"

AccountService::AccountService()
{

}

AccountService::~AccountService()
{

}

void AccountService::RegisterAccount(unsigned int id, Account* account)
{
    if (this->IsAccountRegistered(id))
    {
        throw "break";
    }

    this->accounts[id] = account;
}

void AccountService::UnregisterAccount(unsigned int id)
{
    if (!this->IsAccountRegistered(id))
    {
        throw "break";
    }

    this->accounts.erase(id);
}

Account* AccountService::GetAccount(unsigned int id)
{
    Account* account = this->accounts[id];
    return account;
}

bool AccountService::IsAccountRegistered(unsigned int id)
{
    return (this->accounts[id] != nullptr);
}
