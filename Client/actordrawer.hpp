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
    void DoDrawNPC(Actor* npc, Vector2 draw_middle, bool on_tile) const;
    void DoDrawCharacter(Character* character, Vector2 draw_middle, bool on_tile) const;

public:
    ActorDrawer();
    ~ActorDrawer();

    void DrawActor(Actor* actor, Vector2 draw_middle) const;
    void DrawActorOnTile(Actor* actor, Vector2 tile_middle) const;

};
#endif // ACTORDRAWER_HPP_INCLUDE
