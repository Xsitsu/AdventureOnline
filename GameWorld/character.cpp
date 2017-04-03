#include "character.hpp"

Character::Character() : Actor(), character_id(0), name("N/A"), gender(Character::GENDER_FEMALE), skin(Character::SKIN_WHITE)
{

}

Character::~Character()
{

}

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