#include "maptile.hpp"

MapTile::MapTile() : sprite_id(0), move_permissions(MapTile::MOVEPERM_NONE), warp(nullptr)
{

}

MapTile::~MapTile()
{
    delete this->warp;
}

bool MapTile::TileIsWalkable(Actor* actor) const
{
    bool can_walk = false;

    switch(this->move_permissions)
    {
    case MOVEPERM_NONE:
        can_walk = true;
        break;

    case MOVEPERM_NPC_WALL:
        can_walk = !actor->IsNPC();
        break;

    default:
        break;
    }

    return can_walk;
}

void MapTile::SetSpriteId(unsigned int sprite_id)
{
    this->sprite_id = sprite_id;
}

unsigned int MapTile::GetSpriteId() const
{
    return this->sprite_id;
}

void MapTile::SetMovementPermissions(MovementPermissions permissions)
{
    this->move_permissions = permissions;
}

MapTile::MovementPermissions MapTile::GetMovementPermissions() const
{
    return this->move_permissions;
}

void MapTile::SetMapWarp(MapWarpBase *warp)
{
    this->warp = warp;
}

MapWarpBase* MapTile::GetMapWarp() const
{
    return this->warp;
}
