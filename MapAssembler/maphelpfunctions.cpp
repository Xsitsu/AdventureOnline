#include "maphelpfunctions.hpp"

#include <iostream>

void OutputMapData(Map *map)
{
    Vector2 map_size = map->GetSize();

    std::cout << "_____________________________________" << std::endl;
    std::cout << "Started output for map#" << map->GetMapId() << std::endl;
    std::cout << "Map Size: " << map_size.x << "/" << map_size.y << std::endl;
    std::cout << "_____________________________________" << std::endl;

    int num_warps = 0;

    for (int y = 0; y < map_size.y; y++)
    {
        std::cout << std::endl;
        std::cout << "_____________________________________" << std::endl;
        std::cout << "Output for y = " << y << std::endl;

        for (int x = 0; x < map_size.x; x++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            MapWarpBase *warp = tile.GetMapWarp();

            std::cout << "[" << x << "/" << y << "]";
            std::cout << "\t" << "SpriteId: " << tile.GetSpriteId();
            std::cout << "\t" << "MovePerm: " << (int)tile.GetMovementPermissions();
            if (warp)
            {
                std::cout << "\t" << "Warp: " << warp->GetTargetMapId() << "/"
                << warp->GetTargetCoordinates().x << "/" << warp->GetTargetCoordinates().y
                << " | " << (int)warp->GetWarpType();

                num_warps++;
            }
            std::cout << std::endl;
        }
    }

    std::cout << "_____________________________________" << std::endl;
    std::cout << "Total number of warps: " << num_warps << std::endl;
    std::cout << std::endl << std::endl;
}

void PrintMap(Map *map)
{
    Vector2 map_size = map->GetSize();

    std::cout << "Printing Map#" << map->GetMapId() << std::endl;
    std::cout << "Map Size: " << map_size.x << "/" << map_size.y << std::endl;

    std::cout << "_____________________________________" << std::endl;
    std::cout << "Tiles" << std::endl;

    for (int y = 0; y < map_size.y; y++)
    {
        for (int x = 0; x < map_size.x; x++)
        {
            std::cout << map->GetTile(Vector2(x, y)).GetSpriteId() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "_____________________________________" << std::endl;
    std::cout << "Movement Permissions" << std::endl;
    for (int y = 0; y < map_size.y; y++)
    {
        for (int x = 0; x < map_size.x; x++)
        {
            std::cout << (int)map->GetTile(Vector2(x, y)).GetMovementPermissions() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
