#ifndef GAMESTATECHARACTERVIEWMAKE_HPP_INCLUDE
#define GAMESTATECHARACTERVIEWMAKE_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateCharacterViewMake : public GameStateBase
{
protected:

public:
    GameStateCharacterViewMake(Game* game): GameStateBase(game) {}

    virtual void Enter();

    virtual std::string GetStateName() { return "CharacterViewMake"; }
};

#endif // GAMESTATECHARACTERVIEWMAKE_HPP_INCLUDE
