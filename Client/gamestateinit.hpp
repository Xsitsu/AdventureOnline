#ifndef GAMESTATEINIT_HPP_INCLUDE
#define GAMESTATEINIT_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateInit : public GameStateBase
{
protected:

public:
    GameStateInit(Game* game);

    virtual void Tick();

    virtual std::string GetStateName() { return "Init"; }
};

#endif // GAMESTATEINIT_HPP_INCLUDE
