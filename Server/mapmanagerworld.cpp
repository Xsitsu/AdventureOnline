#include "mapmanagerworld.hpp"

MapManagerWorld::MapManagerWorld(World *world) : world(world)
{

}

MapManagerWorld::~MapManagerWorld()
{

}

void MapManagerWorld::RequestMapLoad(Map *map)
{
    this->world->LoadMap(map->GetMapId());
}

void MapManagerWorld::RequestMapUnload(Map *map)
{
    this->world->UnloadMap(map->GetMapId());
}

Map* MapManagerWorld::GetMapFromId(unsigned int id)
{
    return this->world->GetMap(id);
}
