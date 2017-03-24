#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "main.h"

#include "GameUtil/vector2.hpp"

class Map;

class DLL_EXPORT Actor
{
public:
    // This allows you to compute backwards direction by doing (current_direction + 2)%4
    enum Direction { DIR_UP = 0, DIR_LEFT, DIR_DOWN, DIR_RIGHT };

protected:
    Map* current_map;
    Vector2 map_position;

    Direction direction;

    bool has_nowall;

    unsigned short health;
    unsigned short max_health;

public:
    Actor();
    virtual ~Actor();

    virtual bool IsNPC() const = 0;
    virtual bool IsPlayer() const = 0;

    void EnterMap(Map* map);
    void ExitMap(Map* map);
    void Warp(Map* map, Vector2 coords);
    void Move(Vector2 coords);

    Vector2 GetPosition() const;

    Direction GetDirection() const;
    void SetDirection(Direction direction);

    bool GetHasNowall() const;
    void SetHasNowall(bool val);

};
#endif // ACTOR_HPP_INCLUDE
