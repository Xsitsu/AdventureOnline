#ifndef ACTORSTATE_HPP_INCLUDE
#define ACTORSTATE_HPP_INCLUDE

#include "main.h"

#include "GameUtil/timer.hpp"

class Actor;

#include "actor.hpp"

class DLL_EXPORT ActorStateBase
{
protected:
    Actor* actor;
    Timer timer;

public:
    ActorStateBase(Actor* actor) : actor(actor) {}
    virtual ~ActorStateBase() {}

    virtual void Enter()
    {
        timer.Start();
    }
    virtual void Exit() {}
    virtual void Update() = 0;
    virtual double GetPercentDone() = 0;
    virtual bool CanMove() = 0;
    virtual bool CanAttack() = 0;

    virtual bool IsStanding() { return false; }
    virtual bool IsMoving() { return false; }
    virtual bool IsAttacking() { return false; }
    virtual bool IsDieing() { return false; }
};

class DLL_EXPORT ActorStateStand : public ActorStateBase
{
protected:

public:
    ActorStateStand(Actor* actor);

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsStanding();
};

class DLL_EXPORT ActorStateTurn : public ActorStateBase
{
protected:

public:
    ActorStateTurn(Actor* actor);

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsStanding();
};

class DLL_EXPORT ActorStateWalk : public ActorStateBase
{
protected:

public:
    ActorStateWalk(Actor* actor);

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsMoving();
};

class DLL_EXPORT ActorStateAttack : public ActorStateBase
{
protected:

public:
    ActorStateAttack(Actor *actor);
    virtual ~ActorStateAttack();

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsAttacking();
};

class DLL_EXPORT ActorStateFeignAttack : public ActorStateAttack
{
public:
    ActorStateFeignAttack(Actor *actor);
    virtual void Update();
};

class DLL_EXPORT ActorStateDead : public ActorStateBase
{
public:
    ActorStateDead(Actor *actor);
    virtual ~ActorStateDead();

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsDieing();
};

class DLL_EXPORT ActorStateRevive : public ActorStateBase
{
public:
    ActorStateRevive(Actor *actor);
    virtual ~ActorStateRevive();

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual double GetPercentDone();
    virtual bool CanMove();
    virtual bool CanAttack();

    virtual bool IsStanding();
};

#endif // ACTORSTATE_HPP_INCLUDE
