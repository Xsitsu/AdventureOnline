#ifndef GAMESTATETITLEMAKE_HPP_INCLUDE
#define GAMESTATETITLEMAKE_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateTitleMake : public GameStateBase
{
protected:

public:
    GameStateTitleMake(Game* game): GameStateBase(game) {}

    virtual void Enter();

    virtual std::string GetStateName() { return "TitleMake"; }
};

#endif // GAMESTATETITLEMAKE_HPP_INCLUDE
