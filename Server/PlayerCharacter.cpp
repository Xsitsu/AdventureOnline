#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(int PID, string name, int posY, int posX, int mapID, int strength, int endurance, int intelligence)
{
    i_playerID = PID;
    i_posX = posX;
    i_posY = posY;
    i_map = mapID;
    i_str = strength;
    i_end = endurance;
    i_int = intelligence;
    s_Name = name;
    //ctor
}

PlayerCharacter::~PlayerCharacter()
{
    //dtor
}

PlayerCharacter::PlayerCharacter(const PlayerCharacter& other)
{
    s_Name = other.s_Name;
    i_playerID = other.i_playerID;
    i_posX = other.i_posX;
    i_posY = other.i_posY;
    i_map = other.i_map;
    i_str = other.i_str;
    i_end = other.i_end;
    i_int = other.i_int;
    //copy ctor
}

PlayerCharacter& PlayerCharacter::operator=(const PlayerCharacter& other)
{
    if (this == &other) return *this; // handle self assignment
    s_Name = other.s_Name;
    i_playerID = other.i_playerID;
    i_posX = other.i_posX;
    i_posY = other.i_posY;
    i_map = other.i_map;
    i_str = other.i_str;
    i_end = other.i_end;
    i_int = other.i_int;//assignment operator
    return *this;
}
