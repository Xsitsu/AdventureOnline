#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "main.h"

#include "GameUtil/vector2.hpp"

class ActorStateBase;
class ActorManagerBase;

#include "actorstate.hpp"
#include "actormanager.hpp"

class Map;

class DLL_EXPORT Actor
{
public:
    // This allows you to compute backwards direction by doing (current_direction + 2)%4
    enum Direction { DIR_UP = 0, DIR_LEFT, DIR_DOWN, DIR_RIGHT };

protected:
    ActorManagerBase *actor_manager;

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

    void SetActorManager(ActorManagerBase *manager);
    ActorManagerBase* GetActorManager() const;

    void EnterMap(Map* map);
    void ExitMap(Map* map);
    void Warp(Map* map, Vector2 coords);
    void Turn(Direction direction);
    void Move(Vector2 coords);
    void Attack();
    void FeignAttack();

    void SetMaxHealth( unsigned short val) { max_health = val; }
    void SetHealth( unsigned short val);
    void SetStrength( unsigned short val ) { strength = val; }
    void SetEndurance( unsigned short val ) { endurance = val; }

    unsigned short GetMaxHealth() { return max_health; }
    unsigned short GetHealth() { return health; }
    unsigned short GetStrength() { return strength; }
    unsigned short GetEndurance() { return endurance; }

    void TakeDamage(unsigned short value);
    bool IsDead() const;

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
    bool IsAttacking();
    bool IsDieing();
    double GetStatePercentDone();

};
#endif // ACTOR_HPP_INCLUDE
