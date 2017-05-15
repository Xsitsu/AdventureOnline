#include "mapgenfunctions.hpp"

Map* GenerateMap2()
{
    Map *map = new Map(2);
    map->CreateMap(Vector2(7, 13));

    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 13; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetMovementPermissions(MapTile::MOVEPERM_WALL);
        }
    }


    for (int x = 4; x < 7; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetSpriteId(3);
            tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
        }
    }

    map->GetTile(Vector2(4, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));
    map->GetTile(Vector2(5, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));
    map->GetTile(Vector2(6, 0)).SetMapWarp(new MapWarpRegular(map, 1, Vector2(3, 3)));


    for (int x = 0; x < 3; x++)
    {
        for (int y = 5; y < 13; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));
            tile.SetSpriteId(3);
            tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
        }
    }

    for (int y = 5; y < 8; y++)
    {
        MapTile &tile = map->GetTile(Vector2(3, y));
        tile.SetSpriteId(3);
        tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
    }

    return map;
}

