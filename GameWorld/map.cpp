#include "map.hpp"

#include <sstream>
#include <iostream>

#include "mapwarpregular.hpp"

Map::Map(unsigned int id) : map_manager(nullptr), map_id(id), is_loaded(false), tiles(nullptr)
{

}

Map::~Map()
{
    if (this->IsMapLoaded())
    {
        this->UnloadMap();
    }
}

void Map::SetMapManager(MapManagerBase *map_manager)
{
    this->map_manager = map_manager;
}

MapManagerBase* Map::GetMapManager() const
{
    return this->map_manager;
}


unsigned int Map::GetMapId() const
{
    return this->map_id;
}

void Map::DebugTestLoad()
{
    Map *map = this;


    map->CreateMap(Vector2(7, 14));

    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 14; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetMovementPermissions(MapTile::MOVEPERM_WALL);
        }
    }


    for (int x = 4; x < 7; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetSpriteId(3);
            tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
        }
    }

    map->GetTile(Vector2(4, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));
    map->GetTile(Vector2(5, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));
    map->GetTile(Vector2(6, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));


    for (int x = 0; x < 3; x++)
    {
        for (int y = 5; y < 14; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetSpriteId(3);
            tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
        }
    }

    for (int y = 5; y < 9; y++)
    {
        MapTile &tile = map->GetTile(Vector2(3, y));
        tile.SetSpriteId(3);
        tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
    }
}

void Map::CreateMap(Vector2 size)
{
    if (!this->IsMapLoaded())
    {
        this->size = size;
        this->tiles = new MapTile*[size.x];
        for (uint16_t x = 0; x < size.x; x++)
        {
            this->tiles[x] = new MapTile[size.y];
        }

        this->is_loaded = true;
    }
}

void Map::SaveMap()
{
    if (this->IsMapLoaded())
    {
        std::stringstream ss;
        if (map_id < 1000) ss << "0";
        if (map_id < 100) ss << "0";
        if (map_id < 10) ss << "0";
        ss << map_id;

        MapFile file;
        file.Create(ss.str());
        file.Write(this);
        file.Close();
    }
}

void Map::LoadMap()
{
    if (!this->IsMapLoaded())
    {
        // Enable for debug test load.
        if (false)
        {
            this->DebugTestLoad();
            this->is_loaded = true;
            return;
        }

        std::stringstream ss;
        if (map_id < 1000) ss << "0";
        if (map_id < 100) ss << "0";
        if (map_id < 10) ss << "0";
        ss << this->map_id;

        MapFile file;
        file.Open(ss.str());
        file.Read(this);
        file.Close();

        this->is_loaded = true;
    }
}

void Map::UnloadMap()
{
    if (this->IsMapLoaded())
    {
        // Delete tile data
        for (int x = 0; x < this->size.x; x++)
        {
            delete[] this->tiles[x];
            this->tiles[x] = nullptr;
        }

        delete[] this->tiles;
        this->tiles = nullptr;

        // Clear actor list
        this->actors.clear();

        this->is_loaded = false;
    }
}

bool Map::IsMapLoaded() const
{
    return this->is_loaded;
}

Vector2 Map::GetSize() const
{
    return this->size;
}

bool Map::CoordsAreInBounds(Vector2 coords) const
{
    return (coords.x >= 0 && coords.y >= 0 && coords.x < this->size.x && coords.y < this->size.y);
}

MapTile& Map::GetTile(Vector2 coords)
{
    if (!this->CoordsAreInBounds(coords))
    {
        // ToDo: Replace with valid exception.
        throw "break";
    }

    return this->tiles[coords.x][coords.y];
}

void Map::HandleActorEnter(Actor* actor)
{
    this->actors.push_back(actor);

    if (actor->IsPlayer())
    {
        this->characters.push_back(static_cast<Character*>(actor));
    }
    else if (actor->IsNPC())
    {
        // ToDo: Change static cast type when npcs class implemented.
        this->npcs.push_back(static_cast<Actor*>(actor));
    }
}

void Map::HandleActorLeave(Actor* actor)
{
    this->actors.remove(actor);

    if (actor->IsPlayer())
    {
        this->characters.remove(static_cast<Character*>(actor));
    }
    else if (actor->IsNPC())
    {
        // ToDo: Change static cast type when npcs class implemented.
        this->npcs.remove(static_cast<Actor*>(actor));
    }
}

std::list<Actor*> Map::GetActorList() const
{
    return this->actors;
}

std::list<Character*> Map::GetCharacterList() const
{
    return this->characters;
}

std::list<Actor*> Map::GetNPCList() const
{
    return this->npcs;
}

void Map::Update()
{
    std::list<Actor*>::iterator iter;
    std::list<Actor*> actor_list = this->actors;

    // Need to copy the list because Actor::Update() could do things like warping which
    // changes the actor list of a map which isn't good while we're iterating over it.

    for (iter = actor_list.begin(); iter != actor_list.end(); ++iter)
    {
        Actor* actor = *iter;
        actor->Update();
    }
}
