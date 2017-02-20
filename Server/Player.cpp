#include "Player.h"
#include <string>

Player::Player(int ID, string email, string salty, string hashy): s_emailAddress(email), s_salt(salty), s_hash(hashy)
{
    i_ID = ID;    //ctor
}

Player::~Player()
{
    //dtor
}

Player::Player(const Player& other): s_emailAddress(other.s_emailAddress), s_salt(other.s_salt), s_hash(other.s_hash)
{
    i_ID = other.i_ID;
    //copy ctor
}

Player& Player::operator=(const Player& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    s_emailAddress = rhs.s_emailAddress;
    s_salt = rhs.s_salt;
    s_hash = rhs.s_hash;
     //assignment operator
    return *this;
}
