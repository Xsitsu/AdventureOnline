#ifndef ACTORMANAGERCHARACTER_HPP_INCLUDE
#define ACTORMANAGERCHARACTER_HPP_INCLUDE

#include "GameWorld/actormanager.hpp"

#include "clientconnection.hpp"

#include "world.hpp"

class ActorManagerCharacter : public ActorManagerBase
{
protected:
    ClientConnection *connection;

public:
    ActorManagerCharacter(ClientConnection *connection);
    virtual ~ActorManagerCharacter();

    virtual void SignalMove(Actor *signalto, Actor *other);
    virtual void SignalTurn(Actor *signalto, Actor *other);
    virtual void SignalMapEnter(Actor *signalto, Actor *other);
    virtual void SignalMapLeave(Actor *signalto, Actor *other);
    virtual void SignalPosition(Actor *signalto, Actor *other);
    virtual void SignalAttack(Actor *signalto, Actor *other);
    virtual void SignalTakeDamage(Actor *signalto, Actor *other, unsigned short taken_damage);
    virtual void SignalDied(Actor *signalto, Actor *other);
};

#endif // ACTORMANAGERCHARACTER_HPP_INCLUDE
