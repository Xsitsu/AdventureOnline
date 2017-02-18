#ifndef GAMESTATEQUIT_HPP_INCLUDE
#define GAMESTATEQUIT_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateQuit : public GameStateBase
{
protected:

public:
    GameStateQuit(Game* game);

    virtual void Enter();
    virtual void Tick();

    virtual std::string GetStateName() { return "Quit"; }
};

#endif // GAMESTATEQUIT_HPP_INCLUDE
