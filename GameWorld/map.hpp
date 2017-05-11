#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include "main.h"

#include <list>

class MapTile;
class MapWarpData;

#include "actor.hpp"
#include "character.hpp"
#include "maptile.hpp"

#include "GameUtil/vector2.hpp"

class MapFile;

class MapManagerBase;

#include "mapfile.hpp"
#include "mapmanager.hpp"

class DLL_EXPORT Map
{
    friend class MapFile;

protected:
    MapManagerBase *map_manager;

    unsigned int map_id;
    bool is_loaded;

    MapTile** tiles;

    Vector2 size;

    std::list<Actor*> actors;
    std::list<Character*> characters;
    std::list<Actor*> npcs;

    void DebugTestLoad();

public:
    Map(unsigned int id);
    ~Map();

    void SetMapManager(MapManagerBase *map_manager);
    MapManagerBase* GetMapManager() const;

    unsigned int GetMapId() const;

    void SaveMap();
    void LoadMap();
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

    void Update();
};
#endif // MAP_HPP_INCLUDE
