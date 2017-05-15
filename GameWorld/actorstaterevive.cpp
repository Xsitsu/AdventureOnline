#include "actorstate.hpp"

ActorStateRevive::ActorStateRevive(Actor *actor) : ActorStateBase(actor)
{

}

ActorStateRevive::~ActorStateRevive()
{

}

void ActorStateRevive::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateRevive::Exit()
{

}

void ActorStateRevive::Update()
{
    this->actor->SetHealth(this->actor->GetMaxHealth());
    this->actor->Warp(this->actor->GetMap(), Vector2(2, 2));
    this->actor->ChangeState(new ActorStateStand(this->actor));
}

double ActorStateRevive::GetPercentDone()
{
    return 0;
}

bool ActorStateRevive::CanMove()
{
    return false;
}

bool ActorStateRevive::CanAttack()
{
    return false;
}

bool ActorStateRevive::IsStanding()
{
    return true;
}
