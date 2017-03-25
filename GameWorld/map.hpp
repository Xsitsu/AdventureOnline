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
    int map_id;
    bool is_loaded;

    MapTile** tiles;

    Vector2 size;

    std::list<Actor*> actors;


    void DebugTestLoad();

public:
    Map();
    ~Map();

    void LoadMap(int map_id);
    void UnloadMap();
    bool IsMapLoaded() const;

    Vector2 GetSize() const;

    bool CoordsAreInBounds(Vector2 coords) const;
    MapTile& GetTile(Vector2 coords);

    void HandleActorEnter(Actor* actor);
    void HandleActorLeave(Actor* actor);

    std::list<Actor*> GetActorList() const;
};
#endif // MAP_HPP_INCLUDE
