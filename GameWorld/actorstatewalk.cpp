#include "actorstate.hpp"

#include "map.hpp"
#include "maptile.hpp"
#include "mapwarp.hpp"

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
        Map *cur_map = this->actor->GetMap();
        if (cur_map)
        {
            MapTile &cur_tile = cur_map->GetTile(this->actor->GetPosition());
            MapWarpBase *warp = cur_tile.GetMapWarp();

            if (warp)
            {
                // Actor::Warp() makes a call to ChangeState which will
                // destroy this current state object.
                if (warp->HandleWarp(this->actor))
                {
                    return;
                }
            }
        }

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
