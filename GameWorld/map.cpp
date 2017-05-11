#include "map.hpp"

#include <sstream>
#include <iostream>

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
    this->size = Vector2(20, 20);

    this->tiles = new MapTile*[this->size.x];
    for (int x = 0; x < this->size.x; x++)
    {
        this->tiles[x] = new MapTile[this->size.y];

        for (int y = 0; y < this->size.y; y++)
        {
            MapTile& tile = this->tiles[x][y];
            tile.SetSpriteId(1);
            tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
        }
    }

    this->GetTile(Vector2(9, 9)).SetSpriteId(10);
    this->GetTile(Vector2(9, 10)).SetSpriteId(10);
    this->GetTile(Vector2(10, 9)).SetSpriteId(10);
    this->GetTile(Vector2(10, 10)).SetSpriteId(10);

    this->GetTile(Vector2(11, 11)).SetSpriteId(8);
    this->GetTile(Vector2(8, 8)).SetSpriteId(7);
    this->GetTile(Vector2(8, 11)).SetSpriteId(6);
    this->GetTile(Vector2(11, 8)).SetSpriteId(9);

    this->GetTile(Vector2(11, 9)).SetSpriteId(5);
    this->GetTile(Vector2(11, 10)).SetSpriteId(5);

    this->GetTile(Vector2(8, 9)).SetSpriteId(4);
    this->GetTile(Vector2(8, 10)).SetSpriteId(4);

    this->GetTile(Vector2(9, 11)).SetSpriteId(12);
    this->GetTile(Vector2(10, 11)).SetSpriteId(12);

    this->GetTile(Vector2(9, 8)).SetSpriteId(11);
    this->GetTile(Vector2(10, 8)).SetSpriteId(11);
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
        std::stringstream ss;
        if (map_id < 1000) ss << "0";
        if (map_id < 100) ss << "0";
        if (map_id < 10) ss << "0";
        ss << this->map_id;

        MapFile file;
        file.Open(ss.str());
        file.Read(this);
        file.Close();


        //this->DebugTestLoad();

        this->is_loaded = true;

        MapWarpBase *map_warp = new MapWarpBase(this, 2, Vector2(10, 5));
        this->GetTile(Vector2(5, 5)).SetMapWarp(map_warp);
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
