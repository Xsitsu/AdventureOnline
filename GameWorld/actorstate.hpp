#ifndef ACTORSTATE_HPP_INCLUDE
#define ACTORSTATE_HPP_INCLUDE

#include "main.h"

#include "GameUtil/timer.hpp"

class Actor;

#include "actor.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateStand : public ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateTurn : public ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateWalk : public ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateAttack : public ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateFeignAttack : public ActorStateAttack
{
public:
    ActorStateFeignAttack(Actor *actor);
    virtual void Update();
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateDead : public ActorStateBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
ActorStateRevive : public ActorStateBase
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
