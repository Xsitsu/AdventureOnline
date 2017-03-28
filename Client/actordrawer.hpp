#ifndef ACTORDRAWER_HPP_INCLUDE
#define ACTORDRAWER_HPP_INCLUDE

#include <list>

#include "GameWorld/actor.hpp"
#include "GameWorld/character.hpp"

#include "GameUtil/vector2.hpp"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "bitmapservice.hpp"

struct DrawSpecs
{
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_COLOR tint;
    Vector2 sprite_start;
    Vector2 sprite_size;
    Vector2 draw_offset;
    int draw_flags;
};

class ActorDrawer
{
protected:
    std::list<DrawSpecs> DoDrawSpecsNPC(Actor* actor);
    std::list<DrawSpecs> DoDrawSpecsCharacter(Character* character);

public:
    ActorDrawer();
    ~ActorDrawer();

    std::list<DrawSpecs> GetDrawSpecs(Actor* actor);

};
#endif // ACTORDRAWER_HPP_INCLUDE
