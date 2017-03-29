#include "actordrawer.hpp"

ActorDrawer::ActorDrawer()
{

}

ActorDrawer::~ActorDrawer()
{

}

void ActorDrawer::DrawActor(Actor* actor, Vector2 draw_middle) const
{
    if (actor->IsPlayer())
    {
        this->DoDrawCharacter(static_cast<Character*>(actor), draw_middle, false);
    }
    else if(actor->IsNPC())
    {
        this->DoDrawNPC(static_cast<Actor*>(actor), draw_middle, false);
    }
    else
    {
        // ToDo: Replace with better exception.
        // This code should never run though really.
        throw "BREAK";
    }
}

void ActorDrawer::DrawActorOnTile(Actor* actor, Vector2 tile_middle) const
{
    if (actor->IsPlayer())
    {
        this->DoDrawCharacter(static_cast<Character*>(actor), tile_middle, true);
    }
    else if(actor->IsNPC())
    {
        this->DoDrawNPC(static_cast<Actor*>(actor), tile_middle, true);
    }
    else
    {
        // ToDo: Replace with better exception.
        // This code should never run though really.
        throw "BREAK";
    }
}



void ActorDrawer::DoDrawCharacter(Character* character, Vector2 draw_middle, bool on_tile) const
{
    Actor::Direction dir = character->GetDirection();
    Character::Gender gender = character->GetGender();
    Character::Skin skin = character->GetSkin();

    int draw_flags = 0;
    int dir_flag = 0;

    if (dir == Actor::DIR_RIGHT || dir == Actor::DIR_UP)
    {
        draw_flags = ALLEGRO_FLIP_HORIZONTAL;
    }

    if (dir == Actor::DIR_LEFT || dir == Actor::DIR_UP)
    {
        dir_flag = 1;
    }


    // Base character sprite
    int sprite_width = 18;
    int sprite_height = 58;
    int draw_x = (sprite_width * 2 * (int)gender) + (sprite_width * dir_flag);
    int draw_y = (sprite_height * (int)skin);

    Vector2 draw_base;
    if (!on_tile)
    {
        draw_base = draw_middle - Vector2(sprite_width, sprite_height) / 2;
    }
    else
    {
        draw_base = draw_middle - Vector2(sprite_width / 2, sprite_height);
    }

    ALLEGRO_BITMAP* character_bitmap = BitmapService::Instance()->GetBitmap("character_0");

    al_draw_tinted_bitmap_region(character_bitmap, al_map_rgba(255, 255, 255, 255),
                                draw_x, draw_y, sprite_width, sprite_height,
                                draw_base.x, draw_base.y, draw_flags);

}


void ActorDrawer::DoDrawNPC(Actor* npc, Vector2 draw_middle, bool on_tile) const
{

}
