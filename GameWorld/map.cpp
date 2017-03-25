#include "map.hpp"

Map::Map() : map_id(0), is_loaded(false)
{

}

Map::~Map()
{
    if (this->IsMapLoaded())
    {
        this->UnloadMap();
    }
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
}

void Map::LoadMap(int map_id)
{
    if (!this->IsMapLoaded())
    {
        // Do Load

        this->DebugTestLoad();

        this->is_loaded = true;
        this->map_id = map_id;
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
}

void Map::HandleActorLeave(Actor* actor)
{
    this->actors.remove(actor);
}

std::list<Actor*> Map::GetActorList() const
{
    return this->actors;
}
