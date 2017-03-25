#ifndef MAPTILE_HPP_INCLUDE
#define MAPTILE_HPP_INCLUDE

#include "main.h"

#include "actor.hpp"

class DLL_EXPORT MapTile
{
public:
    enum MovementPermissions
    {
        MOVEPERM_NONE,
        MOVEPERM_WALL,
        MOVEPERM_NPC_WALL
    };

protected:
    int sprite_id;
    MovementPermissions move_permissions;

public:
    bool TileIsWalkable(Actor* actor) const;


    void SetSpriteId(int sprite_id);
    int GetSpriteId() const;

    void SetMovementPermissions(MovementPermissions permissions);
    MovementPermissions GetMovementPermissions() const;
};
#endif // MAPTILE_HPP_INCLUDE
