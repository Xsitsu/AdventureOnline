#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "main.h"

#include "vector2.hpp"

class Map;

class DLL_EXPORT Actor
{
public:
    // This allows you to compute backwards direction by doing (current_direction + 2)%4
    enum DIRECTION { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT };

protected:
    Map* current_map;
    Vector2 map_position;

    DIRECTION direction;

    unsigned short health;
    unsigned short max_health;
    unsigned short strength;
    unsigned short endurance;

public:
    virtual bool IsNPC() const = 0;
    virtual bool IsPlayer() const = 0;

    void EnterMap(Map* map);
    void ExitMap(Map* map);
    void Warp(Map* map, Vector2 coords);
    void Move(Vector2 coords);

    void SetMaxHealth( unsigned short val) { max_health = val; }
    void SetHealth( unsigned short val) { health = val; }
    void SetStrength( unsigned short val ) { strength = val; }
    void SetEndurance( unsigned short val ) { endurance = val; }
    void SetDirection( DIRECTION val ) { direction = val; }

    unsigned short GetMaxHealth() { return max_health; }
    unsigned short GetHealth() { return health; }
    unsigned short GetStrength() { return strength; }
    unsigned short GetEndurance() { return endurance; }
    DIRECTION GetDirection() { return direction; }
    Vector2 GetPosition() { return map_position; }
};
#endif // ACTOR_HPP_INCLUDE
