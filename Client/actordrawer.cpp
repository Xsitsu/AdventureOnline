#include "actordrawer.hpp"
#include <sstream>

#include "GameGui/color3.hpp"

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
    std::stringstream hairType;

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


    Color3 draw_tint = Color3(255, 255, 255);
    unsigned char draw_alpha = 255;

    //int hair_id = 0;
    int color_id = static_cast<int>(character->GetHairColor());
    ALLEGRO_BITMAP* hair_bitmap = nullptr;
    ALLEGRO_BITMAP* character_bitmap = nullptr;
    int sprite_width = 0;
    int sprite_height = 0;
    int draw_frame = 0;
    int max_frames = 0;

    int offset_x = 0;
    int offset_y = 0;

    Vector2 hair_offset;

    BitmapService* service = BitmapService::Instance();
    BitmapService::BitmapSets hair_set;

    if (gender == Character::GENDER_FEMALE)
    {
        hair_set = BitmapService::BITMAPSET_HAIR_FEMALE;
    }
    else if (gender == Character::GENDER_MALE)
    {
        hair_set = BitmapService::BITMAPSET_HAIR_MALE;
    }

    hair_bitmap = service->GetBitmap(hair_set, character->GetHair());
    color_id = character->GetHairColor();

    if (character->IsStanding())
    {
        character_bitmap = service->GetBitmap(BitmapService::BITMAPSET_CHARACTER, 0);
        sprite_width = 18;
        sprite_height = 58;

        draw_frame = 0;
        max_frames = 1;

        hair_offset = Vector2(5, 13);
    }
    else if (character->IsMoving())
    {
        character_bitmap = service->GetBitmap(BitmapService::BITMAPSET_CHARACTER, 1);
        sprite_width = 26;
        sprite_height = 61;

        offset_x = 0;
        offset_y = 2;

        max_frames = 4;
        draw_frame = max_frames * character->GetStatePercentDone();
        if (draw_frame > max_frames)
            draw_frame = max_frames;

        hair_offset = Vector2(1, 12);
    }
    else if (character->IsAttacking())
    {
        character_bitmap = service->GetBitmap(BitmapService::BITMAPSET_CHARACTER, 2);
        sprite_width = 24;
        sprite_height = 58;

        offset_x = 0;
        offset_y = 0;

        max_frames = 2;
        draw_frame = max_frames * character->GetStatePercentDone();
        if (draw_frame > max_frames)
            draw_frame = max_frames;

        hair_offset = Vector2(5, 13);
    }
    else if (character->IsDieing())
    {
        character_bitmap = service->GetBitmap(BitmapService::BITMAPSET_CHARACTER, 0);
        sprite_width = 18;
        sprite_height = 58;

        draw_frame = 0;
        max_frames = 1;

        hair_offset = Vector2(5, 13);

        draw_alpha = 160;
    }

    int draw_x = (sprite_width *  draw_frame) + (sprite_width * max_frames * dir_flag) + (sprite_width * max_frames * 2 * (int)gender);
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

    Vector2 top = draw_base + Vector2(offset_x, offset_y);

    // Compensate for females being shorter than males.
    if (gender == Character::GENDER_FEMALE)
    {
        hair_offset = hair_offset - Vector2(0, 1);
    }

    // Hair needs to be moved 1 pixel horizontally depending on if the bitmap is flipped or not.
    if (draw_flags == ALLEGRO_FLIP_HORIZONTAL)
    {
        hair_offset = hair_offset - Vector2(1, 0);
    }
    else
    {
        hair_offset = hair_offset + Vector2(1, 0);
    }


    ALLEGRO_COLOR tint = al_map_rgba(draw_tint.r, draw_tint.g, draw_tint.b, draw_alpha);

    // Actually do drawing.
    al_draw_tinted_bitmap_region(hair_bitmap, tint,
                                56 * dir_flag, 54 * color_id, 28, 54,
                                top.x - hair_offset.x, top.y - hair_offset.y, draw_flags);

    al_draw_tinted_bitmap_region(character_bitmap, tint,
                                draw_x, draw_y, sprite_width, sprite_height,
                                top.x, top.y, draw_flags);

    al_draw_tinted_bitmap_region(hair_bitmap, tint,
                                28 + 56 * dir_flag, 54 * color_id, 28, 54,
                                top.x - hair_offset.x, top.y - hair_offset.y, draw_flags);

}


void ActorDrawer::DoDrawNPC(Actor* npc, Vector2 draw_middle, bool on_tile) const
{

}
