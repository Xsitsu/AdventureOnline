#ifndef CHARACTER_HPP_INCLUDE
#define CHARACTER_HPP_INCLUDE

#include "actor.hpp"

class Account;

class Character : public Actor
{
protected:
    Account* owner;

public:

};

#endif // CHARACTER_HPP_INCLUDE
