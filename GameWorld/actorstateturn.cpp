#include "actorstate.hpp"

ActorStateTurn::ActorStateTurn(Actor* actor) : ActorStateBase(actor)
{

}

void ActorStateTurn::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateTurn::Exit()
{

}

void ActorStateTurn::Update()
{
        if (this->GetPercentDone() >= 1.0)
    {
        this->actor->ChangeState(new ActorStateStand(this->actor));
    }
}

double ActorStateTurn::GetPercentDone()
{
    double p = this->timer.GetMiliSeconds() / 60;
    if (p > 1.0)
    {
        p = 1.0;
    }
    return p;
}

bool ActorStateTurn::CanMove()
{
    return false;
}

bool ActorStateTurn::CanAttack()
{
    return false;
}

bool ActorStateTurn::IsStanding()
{
    return true;
}
