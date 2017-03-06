#include "account.hpp"

Account::Account(unsigned int id, std::string email, std::string salt, std::string _hash) :
    account_id(id), email(email), salt(salt), _hash(_hash), playing_character(nullptr)
{

}

void Account::AddCharacterToList(Character* character)
{

}

void Account::RemoveCharacterFromList(Character* character)
{

}
