#include "map.hpp"

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
