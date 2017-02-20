#ifndef GAMESTATESERVERCONNECT_HPP_INCLUDE
#define GAMESTATESERVERCONNECT_HPP_INCLUDE

#include <ctime>

#include "gamestate.hpp"

class GameStateServerConnect : public GameStateBase
{
protected:
    std::time_t start_time;
    const double CONNECT_TIMEOUT = 10.0;

public:
    GameStateServerConnect(Game* game);

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual std::string GetStateName() { return "ServerConnect"; }
};
#endif // GAMESTATESERVERCONNECT_HPP_INCLUDE
