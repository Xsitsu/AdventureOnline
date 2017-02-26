#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include <list>

#include "actor.hpp"

class Map
{
protected:
    std::list<Actor*> actors;

public:
    Map();
    ~Map();

};

#endif // MAP_HPP_INCLUDE
