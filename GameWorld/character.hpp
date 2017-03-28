#ifndef CHARACTER_HPP_INCLUDE
#define CHARACTER_HPP_INCLUDE

#include <string>

#include "actor.hpp"

class DLL_EXPORT Character : public Actor
{
public:
    enum Gender { GENDER_FEMALE = 0, GENDER_MALE };
    enum Skin { SKIN_WHITE = 0, SKIN_BROWN, SKIN_GREEN };

protected:
    std::string name;
    Gender gender;
    Skin skin;

public:
    Character();
    ~Character();
    Character(const Character&);

    virtual bool IsNPC() const { return false; }
    virtual bool IsPlayer() const { return true; }

    std::string GetName() { return name; }
    void SetName(std::string val) { name = val; }

    void SetGender(Gender gender);
    Gender GetGender() const;

    void SetSkin(Skin skin);
    Skin GetSkin() const;

};
#endif // CHARACTER_HPP_INCLUDE
