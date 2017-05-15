#include "world.hpp"

#include "GameWorld/mapwarp.hpp"
#include <iostream>

#include "mapmanagerworld.hpp"

World::World(unsigned int number_maps): number_maps(number_maps)
{
    this->map_manager = new MapManagerWorld(this);

    this->maps = new Map*[number_maps];
    for (unsigned int i = 0; i < number_maps; i++)
    {
        Map *map = new Map(i);
        map->SetMapManager(this->map_manager);

        this->maps[i] = map;
    }
}

World::~World()
{
    for (unsigned int i = 0; i < this->number_maps; i++)
    {
        if (this->IsMapLoaded(i))
        {
            this->UnloadMap(i);
        }

        delete this->maps[i];
    }
    delete[] this->maps;
}

bool World::IsMapLoaded(unsigned int id)
{
    return this->maps[id]->IsMapLoaded();
}

Map* World::GetMap(unsigned int id)
{
    return this->maps[id];
}

void World::LoadMap(unsigned int id)
{
    Map* map = this->maps[id];
    map->LoadMap();

    std::cout << "Loaded map with id: " << map->GetMapId() << std::endl;

    this->loaded_maps.push_back(map);
}

void World::UnloadMap(unsigned int id)
{
    Map* map = this->maps[id];
    map->UnloadMap();

    this->loaded_maps.remove(map);
}

void World::Update()
{
    std::list<Map*>::iterator iter;
    std::list<Map*> use_loaded_maps = this->loaded_maps;

    //std::cout << "Map ticks: " << std::endl;

    for (iter = use_loaded_maps.begin(); iter != use_loaded_maps.end(); ++iter)
    {
        Map* map = *iter;
        map->Update();

        //std::cout << "\t" << map->GetMapId() << std::endl;
    }
}
