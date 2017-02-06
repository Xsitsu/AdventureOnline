#ifndef GAMESTATE_HPP_DEFINE
#define GAMESTATE_HPP_DEFINE

#include <iostream>
#include <string>

class Game;

#include "game.hpp"

class GameStateBase
{
protected:
    Game* game;

public:
    GameStateBase(Game* game);
    virtual ~GameStateBase() {}

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Tick() = 0;
    virtual void Render() = 0;

    virtual std::string GetStateName() = 0;
};



class GameStateInit : public GameStateBase
{
protected:

public:
    GameStateInit(Game* game);

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual std::string GetStateName() { return "Init"; }
};


class GameStateTitle : public GameStateBase
{
protected:

public:
    GameStateTitle(Game* game);

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual std::string GetStateName() { return "Title"; }
};

#endif // GAMESTATE_HPP_DEFINE
