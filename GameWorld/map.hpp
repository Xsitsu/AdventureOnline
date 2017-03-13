#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include "main.h"

#include <list>

#include "actor.hpp"
#include "maptile.hpp"

#include "GameUtil/vector2.hpp"

class DLL_EXPORT Map
{
protected:
    MapTile** tiles;

    Vector2 size;

    std::list<Actor*> actors;


public:
    bool CoordsAreInBounds(Vector2 coords) const;
    MapTile& GetTile(Vector2 coords);

    void HandleActorEnter(Actor* actor);
    void HandleActorLeave(Actor* actor);
};
#endif // MAP_HPP_INCLUDE
