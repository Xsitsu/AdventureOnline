#include "maptile.hpp"

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

unsigned int MapTile::GetSpriteId() const
{
    return this->sprite_id;
}

MapTile::MovementPermissions MapTile::GetMovementPermissions() const
{
    return this->move_permissions;
}
