#include "actorstate.hpp"

#include <iostream>
#include <list>

#include "character.hpp"
#include "map.hpp"

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
    Map *cur_map = this->actor->GetMap();
    this->actor->SetHealth(this->actor->GetMaxHealth());
    this->actor->Warp(cur_map, Vector2(2, 2));
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
