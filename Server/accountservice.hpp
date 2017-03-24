#ifndef ACCOUNTSERVICE_HPP_INCLUDE
#define ACCOUNTSERVICE_HPP_INCLUDE

#include <unordered_map>

#include "account.hpp"

class AccountService
{
protected:
    std::unordered_map<unsigned int, Account*> accounts;

public:
    AccountService();
    ~AccountService();

    void RegisterAccount(unsigned int id, Account* account);
    void UnregisterAccount(unsigned int id);
    Account* GetAccount(unsigned int id);
    bool IsAccountRegistered(unsigned int id);
};

#endif // ACCOUNTSERVICE_HPP_INCLUDE
