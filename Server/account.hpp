#ifndef ACCOUNT_HPP_INCLUDE
#define ACCOUNT_HPP_INCLUDE

#include <list>

#include "character.hpp"

class Account
{
protected:
    unsigned int account_id;
    std::list<Character*> characters;

    Character* playing_character;

public:
    Account(unsigned int id);

};

#endif // ACCOUNT_HPP_INCLUDE
