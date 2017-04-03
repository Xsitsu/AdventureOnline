#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "main.h"

#include "GameUtil/vector2.hpp"

class ActorStateBase;

#include "actorstate.hpp"

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

    ActorStateBase* state;

    unsigned short health;
    unsigned short max_health;
    unsigned short strength;
    unsigned short endurance;

public:
    Actor();
    virtual ~Actor();

    virtual bool IsNPC() const = 0;
    virtual bool IsPlayer() const = 0;

    void EnterMap(Map* map);
    void ExitMap(Map* map);
    void Warp(Map* map, Vector2 coords);
    void Turn(Direction direction);
    void Move(Vector2 coords);

    void SetMaxHealth( unsigned short val) { max_health = val; }
    void SetHealth( unsigned short val) { health = val; }
    void SetStrength( unsigned short val ) { strength = val; }
    void SetEndurance( unsigned short val ) { endurance = val; }

    unsigned short GetMaxHealth() { return max_health; }
    unsigned short GetHealth() { return health; }
    unsigned short GetStrength() { return strength; }
    unsigned short GetEndurance() { return endurance; }

    Vector2 GetPosition() const;

    Vector2 GetDirectionVector() const;
    Direction GetDirection() const;
    void SetDirection(Direction direction);

    bool GetHasNowall() const;
    void SetHasNowall(bool val);

    Map* GetMap() const;

    void ChangeState(ActorStateBase* state);

    void Update();
    bool CanMove();
    bool CanAttack();
    bool IsStanding();
    bool IsMoving();
    double GetStatePercentDone();

};
#endif // ACTOR_HPP_INCLUDE
