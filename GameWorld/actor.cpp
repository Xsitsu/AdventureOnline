#include "actor.hpp"

#include "map.hpp"

void Actor::EnterMap(Map* map)
{
    map->HandleActorEnter(this);
    this->current_map = map;
}

void Actor::ExitMap(Map* map)
{
    map->HandleActorLeave(this);
    this->current_map = nullptr;
}

void Actor::Warp(Map* map, Vector2 coords)
{
    if (this->current_map != map)
    {
        if (this->current_map)
        {
            this->ExitMap(this->current_map);
        }
        this->EnterMap(map);
    }

    this->map_position = coords;
}

void Actor::Move(Vector2 coords)
{
    this->map_position = coords;
}

Vector2 Actor::GetPosition() const
{
    return this->map_position;
}

Actor::Direction Actor::GetDirection() const
{
    return this->direction;
}
