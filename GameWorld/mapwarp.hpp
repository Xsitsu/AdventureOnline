#ifndef MAPWARP_HPP_INCLUDE
#define MAPWARP_HPP_INCLUDE

class Map;

#include "map.hpp"
#include "actor.hpp"

#include "GameUtil/vector2.hpp"

class DLL_EXPORT MapWarpBase
{
protected:
    Map *from_map;

    unsigned int targ_map_id;
    Vector2 targ_coords;

public:
    MapWarpBase(Map *from_map, unsigned int targ_map_id, Vector2 targ_coords);
    virtual ~MapWarpBase();

    virtual bool HandleWarp(Actor *actor);
};

#endif // MAPWARP_HPP_INCLUDE
