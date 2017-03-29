#ifndef ACCOUNT_HPP_INCLUDE
#define ACCOUNT_HPP_INCLUDE

#include <string>
#include <list>

#include "GameWorld/character.hpp"

class Account
{
protected:
    unsigned int account_id;
    std::string email;
    std::string salt;
    std::string _hash;

    std::list<Character*> character_list;

    Character* playing_character;

public:
    Account(unsigned int id, std::string email, std::string salt, std::string _hash);

    int GetAccountId() const { return this->account_id; }
    std::string GetEmail() const { return this->email; }
    std::string GetSalt() const { return this->salt; }
    std::string GetHash() const { return this->_hash; }

    int GetNumberCharacters() const;
    Character* GetPlayingCharacter() const;
    std::list<Character*> GetCharacterList() const;

    void SetPlayingCharacter(Character* character);

    bool CharacterIsInList(Character* character) const;
    void AddCharacterToList(Character* character);
    void RemoveCharacterFromList(Character* character);
    void ClearCharacterList();
};

#endif // ACCOUNT_HPP_INCLUDE
