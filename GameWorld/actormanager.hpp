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
};

#endif // ACTORMANAGER_HPP_INCLUDE
