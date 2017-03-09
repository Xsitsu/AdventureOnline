#include "map.hpp"

bool Map::CoordsAreInBounds(unsigned short x, unsigned short y) const
{
    return (x >= 0 && y >= 0 && x < this->size_x && y < this->size_y);
}

MapTile& Map::GetTile(unsigned short x, unsigned short y)
{
    if (!this->CoordsAreInBounds(x, y))
    {
        // ToDo: Replace with valid exception.
        throw "break";
    }

    return this->tiles[x][y];
}

void Map::HandleActorEnter(Actor* actor)
{
    this->actors.push_back(actor);
}

void Map::HandleActorLeave(Actor* actor)
{
    this->actors.remove(actor);
}
