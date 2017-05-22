#ifndef MAPTILE_HPP_INCLUDE
#define MAPTILE_HPP_INCLUDE

#include "main.h"

class MapWarpBase;

#include "actor.hpp"
#include "mapwarp.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
MapTile
{
public:
    enum MovementPermissions
    {
        MOVEPERM_NONE,
        MOVEPERM_WALL,
        MOVEPERM_NPC_WALL
    };

protected:
    unsigned int sprite_id;
    MovementPermissions move_permissions;
    MapWarpBase *warp;

public:
    MapTile();
    virtual ~MapTile();

    bool TileIsWalkable(Actor* actor) const;

    void SetSpriteId(unsigned int sprite_id);
    unsigned int GetSpriteId() const;

    void SetMovementPermissions(MovementPermissions permissions);
    MovementPermissions GetMovementPermissions() const;

    void SetMapWarp(MapWarpBase *warp);
    MapWarpBase* GetMapWarp() const;
};
#endif // MAPTILE_HPP_INCLUDE
