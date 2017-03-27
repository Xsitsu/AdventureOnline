#include "actor.hpp"

#include "map.hpp"

#include <iostream>

Actor::Actor() : current_map(nullptr), map_position(0,0), direction(DIR_DOWN), has_nowall(false), health(10), max_health(10), strength(0), endurance(0)
{

}

Actor::~Actor()
{

}

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
    Vector2 diff = coords - this->map_position;
    bool can_move = false;
    if (diff == Vector2(1, 0) && this->direction == DIR_RIGHT)
    {
        can_move = true;
    }
    else if (diff == Vector2(-1, 0) && this->direction == DIR_LEFT)
    {
        can_move = true;
    }
    else if (diff == Vector2(0, 1) && this->direction == DIR_DOWN)
    {
        can_move = true;
    }
    else if (diff == Vector2(0, -1) && this->direction == DIR_UP)
    {
        can_move = true;
    }
    else
    {
        /*
        std::cout << "Bad try move: " << diff.x << "/" << diff.y << " :: ";
        if (this->direction == DIR_LEFT)
        {
            std::cout << "Left";
        }
        else if (this->direction == DIR_RIGHT)
        {
            std::cout << "Right";
        }
        else if (this->direction == DIR_UP)
        {
            std::cout << "Up";
        }
        else if (this->direction == DIR_DOWN)
        {
            std::cout << "Down";
        }

        std::cout << std::endl;
        */
    }

    if (!can_move)
    {
        // ToDo: Replace with something like an invalid movement exception.
        throw "BREAK";
    }

    if (this->has_nowall ||
        (this->current_map->CoordsAreInBounds(coords) && this->current_map->GetTile(coords).TileIsWalkable(this)))
    {
        this->map_position = coords;
    }
    else
    {
        // ToDo: Replace with valid exception.
        throw "BREAK";
    }

}

Vector2 Actor::GetPosition() const
{
    return this->map_position;
}

Actor::Direction Actor::GetDirection() const
{
    return this->direction;
}

void Actor::SetDirection(Direction direction)
{
    this->direction = direction;
}

bool Actor::GetHasNowall() const
{
    return this->has_nowall;
}

void Actor::SetHasNowall(bool val)
{
    this->has_nowall = val;
}
