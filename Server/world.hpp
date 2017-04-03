#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "GameWorld\map.hpp"

class ClientConnection;

class World
{
protected:
    unsigned int number_maps;
    Map** maps;
    std::list<Map*> loaded_maps;
    std::list<ClientConnection*>* clients_in_maps;

public:
    World(unsigned int number_maps);
    ~World();

    // TODO: These need to throw exceptions if provided out of range ids.
    bool IsMapLoaded(unsigned int id);
    Map* GetMap(unsigned int id);
    void LoadMap(unsigned int id);
    void UnloadMap(unsigned int id);

    void RegisterClientInMap(ClientConnection* client, unsigned int map_id);
    void UnregisterClientInMap(ClientConnection* client, unsigned int map_id);

    std::list<ClientConnection*> GetClientsInMap(unsigned int map_id) const;

    void Update();
};
#endif // WORLD_HPP_INCLUDE
