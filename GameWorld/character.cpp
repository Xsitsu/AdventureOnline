#include "character.hpp"


Character::Character()
{
    name = "";
    current_map = nullptr;

    direction = DIRECTION::DIR_UP;
    health = 0;
    max_health = 0;
    strength = 0;
    endurance = 0;
}
Character::~Character()
{

}
Character::Character(const Character& val)
{
    name = val.name;
    current_map = val.current_map;

    direction = val.direction;
    health = val.health;
    max_health = val.max_health;
    strength = val.strength;
    endurance = val.endurance;
    map_position = val.map_position;
}
