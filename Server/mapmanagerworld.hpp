#ifndef MAPMANAGERWORLD_HPP_INCLUDE
#define MAPMANAGERWORLD_HPP_INCLUDE

#include "GameWorld/mapmanager.hpp"

#include "world.hpp"

class MapManagerWorld : public MapManagerBase
{
protected:
    World *world;

public:
    MapManagerWorld(World *world);
    virtual ~MapManagerWorld();

    virtual void RequestMapLoad(Map *map);
    virtual void RequestMapUnload(Map *map);

    virtual Map* GetMapFromId(unsigned int id);
};

#endif // MAPMANAGERWORLD_HPP_INCLUDE
