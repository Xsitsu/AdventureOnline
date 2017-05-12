#include "mapgenfunctions.hpp"
#include "maphelpfunctions.hpp"

int main()
{
    Map *map1 = GenerateMap1();
    Map *map2 = GenerateMap2();

    map1->SaveMap();
    map2->SaveMap();

    Map *map1l = new Map(1);
    map1l->LoadMap();

    Map *map2l = new Map(2);
    map2l->LoadMap();

    //OutputMapData(map1);
    //OutputMapData(map1l);

    //OutputMapData(map2);
    //OutputMapData(map2l);

    //PrintMap(map2);
    //PrintMap(map2l);

    return 0;
}
