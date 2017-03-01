#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

class Map;

class Actor
{
public:
    // This allows you to compute backwards direction by doing (current_direction + 2)%4
    enum DIRECTION { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT };

protected:
    Map* current_map;
    unsigned short x_coord;
    unsigned short y_coord;
    DIRECTION direction;

    unsigned short health;
    unsigned short max_health;

public:

};
#endif // ACTOR_HPP_INCLUDE
