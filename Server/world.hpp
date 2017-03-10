#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "GameWorld\map.hpp"

class World
{
protected:
    unsigned int number_maps;
    Map** maps;

public:
    World(unsigned int number_maps);
    ~World();

    // TODO: These need to throw exceptions if provided out of range ids.
    bool IsMapLoaded(unsigned int id);
    Map* GetMap(unsigned int id);
    void LoadMap(unsigned int id);
    void UnloadMap(unsigned int id);

};
#endif // WORLD_HPP_INCLUDE
