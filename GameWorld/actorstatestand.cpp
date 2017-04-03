#include "actorstate.hpp"

ActorStateStand::ActorStateStand(Actor* actor) : ActorStateBase(actor)
{

}

void ActorStateStand::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateStand::Exit()
{

}

void ActorStateStand::Update()
{

}

double ActorStateStand::GetPercentDone()
{
    return 1.0;
}

bool ActorStateStand::CanMove()
{
    return true;
}

bool ActorStateStand::CanAttack()
{
    return true;
}

bool ActorStateStand::IsStanding()
{
    return true;
}
