#include "mapwarpregular.hpp"

MapWarpRegular::MapWarpRegular(Map *from_map, unsigned int targ_map_id, Vector2 targ_coords) :
    MapWarpBase(from_map, targ_map_id, targ_coords)
{

}

MapWarpRegular::~MapWarpRegular()
{

}

uint8_t MapWarpRegular::GetWarpType() const
{
    return 1;
}
