#include "account.hpp"

Account::Account(unsigned int id, std::string email, std::string salt, std::string _hash) :
    account_id(id), email(email), salt(salt), _hash(_hash), playing_character(nullptr)
{

}

int Account::GetNumberCharacters() const
{
    return this->character_list.size();
}

Character* Account::GetPlayingCharacter() const
{
    return this->playing_character;
}

std::list<Character*> Account::GetCharacterList() const
{
    return this->character_list;
}

void Account::SetPlayingCharacter(Character* character)
{
    this->playing_character = character;
}

bool Account::CharacterIsInList(Character* character) const
{
    std::list<Character*>::const_iterator iter;
    for (iter = this->character_list.begin(); iter != this->character_list.end(); ++iter)
    {
        if (*iter == character)
            return true;
    }

    return false;
}

void Account::AddCharacterToList(Character* character)
{
    if (!this->CharacterIsInList(character))
    {
        this->character_list.push_back(character);
    }
}

void Account::RemoveCharacterFromList(Character* character)
{
    if (this->CharacterIsInList(character))
    {
        this->character_list.remove(character);
    }
}

void Account::ClearCharacterList()
{
    while (!this->character_list.empty())
    {
        delete this->character_list.front();
        this->character_list.pop_front();
    }
}
