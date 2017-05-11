#include "actormanagercharacter.hpp"

ActorManagerCharacter::ActorManagerCharacter(ClientConnection *connection) : connection(connection)
{

}

ActorManagerCharacter::~ActorManagerCharacter()
{

}

void ActorManagerCharacter::SignalMove(Actor *signalto, Actor *other)
{
    if (other->IsPlayer())
    {
        this->connection->SendCharacterWalk(static_cast<Character*>(other));
    }
}

void ActorManagerCharacter::SignalTurn(Actor *signalto, Actor *other)
{
    if (other->IsPlayer())
    {
        this->connection->SendCharacterTurn(static_cast<Character*>(other));
    }
}

void ActorManagerCharacter::SignalMapEnter(Actor *signalto, Actor *other)
{
    if (other->IsPlayer())
    {
        this->connection->SendCharacterMapEnter(static_cast<Character*>(other));
    }
}

void ActorManagerCharacter::SignalMapLeave(Actor *signalto, Actor *other)
{
    if (other->IsPlayer())
    {
        this->connection->SendCharacterMapLeave(static_cast<Character*>(other));
    }
}

void ActorManagerCharacter::SignalPosition(Actor *signalto, Actor *other)
{
    if (other->IsPlayer())
    {
        this->connection->SendCharacterPosition(static_cast<Character*>(other));
    }
}
