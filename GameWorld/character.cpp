#include "character.hpp"

void Character::SetGender(Character::Gender gender)
{
    this->gender = gender;
}

Character::Gender Character::GetGender() const
{
    return this->gender;
}

void Character::SetSkin(Character::Skin skin)
{
    this->skin = skin;
}

Character::Skin Character::GetSkin() const
{
    return this->skin;
}
