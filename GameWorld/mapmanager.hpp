#ifndef MAPMANAGER_HPP_INCLUDE
#define MAPMANAGER_HPP_INCLUDE

class Map;

#include "map.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
MapManagerBase
{
protected:

public:
    virtual ~MapManagerBase() {}

    virtual void RequestMapLoad(Map *map) = 0;
    virtual void RequestMapUnload(Map *map) = 0;

    virtual Map* GetMapFromId(unsigned int id) = 0;
};

#endif // MAPMANAGER_HPP_INCLUDE
