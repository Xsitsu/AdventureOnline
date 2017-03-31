#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include "main.h"

#include <list>

#include "actor.hpp"
#include "character.hpp"
#include "maptile.hpp"

#include "GameUtil/vector2.hpp"

class MapFile;

#include "mapfile.hpp"

class DLL_EXPORT Map
{
    friend class MapFile;

protected:
    unsigned int map_id;
    bool is_loaded;

    MapTile** tiles;

    Vector2 size;

    std::list<Actor*> actors;
    std::list<Character*> characters;
    std::list<Actor*> npcs;

    void DebugTestLoad();

public:
    Map();
    ~Map();

    unsigned int GetMapId() const;

    void SaveMap();
    void LoadMap(int map_id);
    void UnloadMap();
    bool IsMapLoaded() const;

    Vector2 GetSize() const;

    bool CoordsAreInBounds(Vector2 coords) const;
    MapTile& GetTile(Vector2 coords);

    void HandleActorEnter(Actor* actor);
    void HandleActorLeave(Actor* actor);

    std::list<Actor*> GetActorList() const;
    std::list<Character*> GetCharacterList() const;
    std::list<Actor*> GetNPCList() const;
};
#endif // MAP_HPP_INCLUDE
