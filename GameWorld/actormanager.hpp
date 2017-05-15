#ifndef ACTORMANAGER_HPP_INCLUDE
#define ACTORMANAGER_HPP_INCLUDE

class Actor;

#include "actor.hpp"

class ActorManagerBase
{
protected:

public:
    virtual ~ActorManagerBase() {}

    virtual void SignalMove(Actor *signalto, Actor *other) = 0;
    virtual void SignalTurn(Actor *signalto, Actor *other) = 0;
    virtual void SignalMapEnter(Actor *signalto, Actor *other) = 0;
    virtual void SignalMapLeave(Actor *signalto, Actor *other) = 0;
    virtual void SignalPosition(Actor *signalto, Actor *other) = 0;
    virtual void SignalAttack(Actor *signalto, Actor *other) = 0;
    virtual void SignalTakeDamage(Actor *signalto, Actor *other, unsigned short taken_damage) = 0;
    virtual void SignalDied(Actor *signalto, Actor *other) = 0;
    virtual void SignalHealth(Actor *signalto, Actor *other) = 0;
};

#endif // ACTORMANAGER_HPP_INCLUDE
