#ifndef GAMESTATEACCOUNTCREATIONMAKE_H
#define GAMESTATEACCOUNTCREATIONMAKE_H

#include "gamestate.hpp"

class GameStateAccountCreationMake : public GameStateBase
{

    public:
        GameStateAccountCreationMake(Game * game): GameStateBase(game){}

        virtual void Enter();

        virtual std::string GetStateName() { return "AccountCreationMake"; }
};

#endif // GAMESTATEACCOUNTCREATIONMAKE_H
