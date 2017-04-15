#ifndef CHARACTER_HPP_INCLUDE
#define CHARACTER_HPP_INCLUDE

#include <string>

#include "actor.hpp"

class DLL_EXPORT Character : public Actor
{
public:
    enum Gender { GENDER_FEMALE = 0, GENDER_MALE };
    enum Skin { SKIN_WHITE = 0, SKIN_BROWN, SKIN_GREEN };
    enum Hair { HAIR_ONE = 0, HAIR_TWO};
    enum HairColor { HAIR_BROWN, HAIR_BLACK, HAIR_WHITE, HAIR_PURPLE,
                     HAIR_LIGHT_BLUE, HAIR_RED, HAIR_GREEN, HAIR_DARK_BLUE,
                     HAIR_YELLOW, HAIR_PINK};

protected:
    unsigned int character_id;

    std::string name;
    Gender gender;
    Skin skin;
    Hair hair;
    HairColor hairColor;

public:
    Character();
    ~Character();

    virtual bool IsNPC() const { return false; }
    virtual bool IsPlayer() const { return true; }

    unsigned int GetCharacterId() const { return this->character_id; }
    void SetCharacterId(unsigned int id) { this->character_id = id; }

    std::string GetName() const { return name; }
    void SetName(std::string val) { name = val; }

    void SetGender(Gender gender);
    Gender GetGender() const;

    void SetSkin(Skin skin);
    Skin GetSkin() const;

    void SetHair( Hair val) { hair = val; }
    Hair GetHair() const { return hair; }

    void SetHairColor( HairColor val ) { hairColor = val; }
    HairColor GetHairColor() const { return hairColor; }

};
#endif // CHARACTER_HPP_INCLUDE
