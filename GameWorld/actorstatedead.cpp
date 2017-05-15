#include "actorstate.hpp"

ActorStateDead::ActorStateDead(Actor *actor) : ActorStateBase(actor)
{

}

ActorStateDead::~ActorStateDead()
{

}

void ActorStateDead::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateDead::Exit()
{

}

void ActorStateDead::Update()
{
    if (this->GetPercentDone() >= 1.0)
    {
        this->actor->ChangeState(new ActorStateRevive(this->actor));
    }
}

double ActorStateDead::GetPercentDone()
{
    double p = this->timer.GetMiliSeconds() / 1000;
    if (p > 1.0)
    {
        p = 1.0;
    }
    return p;
}

bool ActorStateDead::CanMove()
{
    return false;
}

bool ActorStateDead::CanAttack()
{
    return false;
}

bool ActorStateDead::IsDieing()
{
    return true;
}
