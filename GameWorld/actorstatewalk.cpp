#include "actorstate.hpp"

ActorStateWalk::ActorStateWalk(Actor* actor) : ActorStateBase(actor)
{

}

void ActorStateWalk::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateWalk::Exit()
{

}

void ActorStateWalk::Update()
{
    if (this->GetPercentDone() >= 1.0)
    {
        this->actor->ChangeState(new ActorStateStand(this->actor));
    }
}

double ActorStateWalk::GetPercentDone()
{
    double p = this->timer.GetMiliSeconds() / 480;
    if (p > 1.0)
    {
        p = 1.0;
    }
    return p;
}

bool ActorStateWalk::CanMove()
{
    return false;
}

bool ActorStateWalk::CanAttack()
{
    return false;
}

bool ActorStateWalk::IsMoving()
{
    return true;
}
