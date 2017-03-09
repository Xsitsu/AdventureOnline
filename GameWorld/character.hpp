#ifndef CHARACTER_HPP_INCLUDE
#define CHARACTER_HPP_INCLUDE

#include <string>

#include "actor.hpp"

class DLL_EXPORT Character : public Actor
{
protected:
    std::string name;

public:
    virtual bool IsNPC() const { return false; }
    virtual bool IsPlayer() const { return true; }
};
#endif // CHARACTER_HPP_INCLUDE
