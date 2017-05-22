#ifndef MAPWARP_HPP_INCLUDE
#define MAPWARP_HPP_INCLUDE

class Map;

#include "map.hpp"
#include "actor.hpp"

#include "GameUtil/vector2.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
MapWarpBase
{
protected:
    Map *from_map;

    unsigned int targ_map_id;
    Vector2 targ_coords;

public:
    MapWarpBase(Map *from_map, unsigned int targ_map_id, Vector2 targ_coords);
    virtual ~MapWarpBase();

    virtual bool HandleWarp(Actor *actor);

    unsigned int GetTargetMapId() const;
    Vector2 GetTargetCoordinates() const;
    virtual uint8_t GetWarpType() const = 0;
};

#endif // MAPWARP_HPP_INCLUDE
