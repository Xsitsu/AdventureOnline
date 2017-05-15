#include "actorstate.hpp"

#include <iostream>

#include "map.hpp"
#include "maptile.hpp"
#include "mapwarp.hpp"

ActorStateAttack::ActorStateAttack(Actor* actor) : ActorStateBase(actor)
{

}

ActorStateAttack::~ActorStateAttack()
{

}

void ActorStateAttack::Enter()
{
    ActorStateBase::Enter();
}

void ActorStateAttack::Exit()
{

}

void ActorStateAttack::Update()
{
    if (this->GetPercentDone() >= 1.0)
    {
        Map *cur_map = this->actor->GetMap();
        Vector2 attack_coords = this->actor->GetPosition() + this->actor->GetDirectionVector();

        std::list<Actor*> actor_list = cur_map->GetActorList();
        std::list<Actor*>::iterator iter;
        for (iter = actor_list.begin(); iter != actor_list.end(); ++iter)
        {
            Actor *act = *iter;
            if (act->GetPosition() == attack_coords)
            {
                if (!act->IsDead())
                {
                    act->TakeDamage(5);
                    if (act->IsDead())
                    {
                        act->ChangeState(new ActorStateDead(act));
                    }
                }
            }
        }

        this->actor->ChangeState(new ActorStateStand(this->actor));
    }
}

double ActorStateAttack::GetPercentDone()
{
    double p = this->timer.GetMiliSeconds() / 480;
    if (p > 1.0)
    {
        p = 1.0;
    }
    return p;
}

bool ActorStateAttack::CanMove()
{
    return false;
}

bool ActorStateAttack::CanAttack()
{
    return false;
}

bool ActorStateAttack::IsAttacking()
{
    return true;
}


ActorStateFeignAttack::ActorStateFeignAttack(Actor *actor) : ActorStateAttack(actor)
{

}

void ActorStateFeignAttack::Update()
{
    if (this->GetPercentDone() >= 1.0)
    {
        this->actor->ChangeState(new ActorStateStand(this->actor));
    }
}
