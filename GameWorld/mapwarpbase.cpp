#include "mapwarp.hpp"

MapWarpBase::MapWarpBase(Map *from_map,  unsigned int targ_map_id, Vector2 targ_coords) :
    from_map(from_map), targ_map_id(targ_map_id), targ_coords(targ_coords)
{

}

MapWarpBase::~MapWarpBase()
{

}

bool MapWarpBase::HandleWarp(Actor *actor)
{
    if (this->from_map->GetMapManager())
    {
        Map *targ_map = this->from_map->GetMapManager()->GetMapFromId(this->targ_map_id);
        actor->Warp(targ_map, this->targ_coords);

        return true;
    }

    return false;
}

unsigned int MapWarpBase::GetTargetMapId() const
{
    return this->targ_map_id;
}

Vector2 MapWarpBase::GetTargetCoordinates() const
{
    return this->targ_coords;
}
