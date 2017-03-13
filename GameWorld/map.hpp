#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include "main.h"

#include <list>

#include "actor.hpp"
#include "maptile.hpp"

class DLL_EXPORT Map
{
protected:
    MapTile** tiles;

    unsigned short size_x;
    unsigned short size_y;

    std::list<Actor*> actors;


public:
    bool CoordsAreInBounds(unsigned short x, unsigned short y) const;
    MapTile& GetTile(unsigned short x, unsigned short y);

    void HandleActorEnter(Actor* actor);
    void HandleActorLeave(Actor* actor);
};
#endif // MAP_HPP_INCLUDE
