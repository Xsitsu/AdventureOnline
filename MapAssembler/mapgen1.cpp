#include "mapgenfunctions.hpp"

Map* GenerateMap1()
{
    Map *map = new Map(1);
    map->CreateMap(Vector2(10, 10));

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            MapTile &tile = map->GetTile(Vector2(x, y));

            if (!((x == 0 || (x == 9)) && (y == 0 || y == 9)))
            {
                tile.SetSpriteId(1);
                tile.SetMovementPermissions(MapTile::MOVEPERM_NONE);
            }
            else
            {
                tile.SetSpriteId(0);
                tile.SetMovementPermissions(MapTile::MOVEPERM_WALL);
            }

        }
    }

    MapTile &tile = map->GetTile(Vector2(3, 3));
    tile.SetSpriteId(2);
    MapWarpRegular *warp = new MapWarpRegular(map, 2, Vector2(5, 1));
    tile.SetMapWarp(warp);

    return map;
}
