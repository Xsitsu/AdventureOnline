#include "actordrawer.hpp"

ActorDrawer::ActorDrawer()
{

}

ActorDrawer::~ActorDrawer()
{

}

std::list<DrawSpecs> ActorDrawer::GetDrawSpecs(Actor* actor)
{
    if (actor->IsPlayer())
    {
        return this->DoDrawSpecsCharacter(static_cast<Character*>(actor));
    }
    else if(actor->IsNPC())
    {
        return this->DoDrawSpecsNPC(static_cast<Actor*>(actor));
    }
    else
    {
        // ToDo: Replace with better exception.
        // This code should never run though really.
        throw "BREAK";
    }
}

std::list<DrawSpecs> ActorDrawer::DoDrawSpecsCharacter(Character* character)
{
    std::list<DrawSpecs> spec_list;

    Character* mychar = character;

    Actor::Direction dir = mychar->GetDirection();
    Character::Gender gender = mychar->GetGender();
    Character::Skin skin = mychar->GetSkin();

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

    DrawSpecs specs;
    specs.draw_flags = draw_flags;
    specs.sprite_start = Vector2(draw_x, draw_y);
    specs.sprite_size = Vector2(sprite_width, sprite_height);
    specs.tint = al_map_rgba(255, 255, 255, 255);
    specs.bitmap = BitmapService::Instance()->GetBitmap("character_0");

    spec_list.push_back(specs);



    return spec_list;
}

std::list<DrawSpecs> ActorDrawer::DoDrawSpecsNPC(Actor* actor)
{
    std::list<DrawSpecs> spec_list;

    // ToDo: Fill in eventually when NPC class is created.

    return spec_list;
}
