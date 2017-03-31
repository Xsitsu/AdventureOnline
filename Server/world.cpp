#include "world.hpp"

#include <iostream>

World::World(unsigned int number_maps): number_maps(number_maps)
{
    this->maps = new Map*[number_maps];
    for (unsigned int i = 0; i < number_maps; i++)
    {
        this->maps[i] = nullptr;
    }

    this->clients_in_maps = new std::list<ClientConnection*>[number_maps];
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
    delete[] this->clients_in_maps;
}

bool World::IsMapLoaded(unsigned int id)
{
    return (this->maps[id] != nullptr);
}

Map* World::GetMap(unsigned int id)
{
    return this->maps[id];
}

void World::LoadMap(unsigned int id)
{
    Map* map = new Map();
    map->LoadMap(id);
    this->maps[id] = map;

    std::cout << "Loaded map with id: " << map->GetMapId() << std::endl;
}

void World::UnloadMap(unsigned int id)
{
    Map* map = this->maps[id];
    map->UnloadMap();
    delete map;
    this->maps[id] = nullptr;
}

void World::RegisterClientInMap(ClientConnection* client, unsigned int map_id)
{
    this->clients_in_maps[map_id].push_back(client);
}

void World::UnregisterClientInMap(ClientConnection* client, unsigned int map_id)
{
    this->clients_in_maps[map_id].remove(client);
}

std::list<ClientConnection*> World::GetClientsInMap(unsigned int map_id) const
{
    return this->clients_in_maps[map_id];
}
