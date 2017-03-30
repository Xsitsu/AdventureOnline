#include "character.hpp"

Character::Character() : character_id(0), name("N/A"), gender(Character::GENDER_FEMALE), skin(Character::SKIN_WHITE)
{

}

Character::Character(const Character& val)
{
    name = val.name;
    current_map = val.current_map;
    gender = val.gender;
    skin = val.skin;
    direction = val.direction;
    health = val.health;
    max_health = val.max_health;
    strength = val.strength;
    endurance = val.endurance;
    map_position = val.map_position;
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
