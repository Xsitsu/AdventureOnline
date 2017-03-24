#ifndef ACTORDRAWER_HPP_INCLUDE
#define ACTORDRAWER_HPP_INCLUDE

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
    int draw_flags;
};

class ActorDrawer
{
protected:
    DrawSpecs DoDrawSpecsNPC(Actor* actor);
    DrawSpecs DoDrawSpecsCharacter(Character* character);

public:
    ActorDrawer();
    ~ActorDrawer();

    DrawSpecs GetDrawSpecs(Actor* actor);

};
#endif // ACTORDRAWER_HPP_INCLUDE
