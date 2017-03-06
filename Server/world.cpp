#include "world.hpp"

World::World(unsigned int number_maps): number_maps(number_maps)
{
    this->maps = new Map*[number_maps];
    for (int i = 0; i < number_maps; i++)
    {
        this->maps[i] = nullptr;
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
    }
    delete[] this->maps;
}

bool World::IsMapLoaded(unsigned int id)
{
    return this->maps[id] != nullptr;
}

Map* World::GetMap(unsigned int id)
{
    return this->maps[id];
}

void World::LoadMap(unsigned int id)
{
    this->maps[id] = new Map();
}

void World::UnloadMap(unsigned int id)
{
    delete this->maps[id];
    this->maps[id] = nullptr;
}
