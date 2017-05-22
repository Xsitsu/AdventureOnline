#ifndef MAPWARPREGULAR_HPP_INCLUDE
#define MAPWARPREGULAR_HPP_INCLUDE

class MapWarpBase;

#include "mapwarp.hpp"


class
#ifdef WINDOWS
DLL_EXPORT
#endif
MapWarpRegular : public MapWarpBase
{
protected:

public:
    MapWarpRegular(Map *from_map, unsigned int targ_map_id, Vector2 targ_coords);
    virtual ~MapWarpRegular();

    virtual uint8_t GetWarpType() const;
};

#endif // MAPWARPREGULAR_HPP_INCLUDE
