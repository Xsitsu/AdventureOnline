#ifndef CHARACTER_HPP_INCLUDE
#define CHARACTER_HPP_INCLUDE

#include <string>

#include "actor.hpp"

class DLL_EXPORT Character : public Actor
{
public:
    enum Gender {GENDER_FEMALE, GENDER_MALE};
    enum Skin {SKIN_WHITE, SKIN_BROWN, SKIN_GREEN};

protected:
    std::string name;
    Gender gender;
    Skin skin;

public:
    virtual bool IsNPC() const { return false; }
    virtual bool IsPlayer() const { return true; }

    void SetGender(Gender gender);
    Gender GetGender() const;

    void SetSkin(Skin skin);
    Skin GetSkin() const;

};
#endif // CHARACTER_HPP_INCLUDE
