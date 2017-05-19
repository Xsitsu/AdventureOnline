#ifndef GAMESTATELOGINAWAITRESPONSE_HPP_INCLUDE
#define GAMESTATELOGINAWAITRESPONSE_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateLoginAwaitResponse : public GameStateBase
{
public:
    GameStateLoginAwaitResponse(Game* game) : GameStateBase(game) {}

    virtual void Render();

    virtual bool HandlePacket(PacketBase* packet);

    virtual std::string GetStateName() { return "LoginAwaitResponse"; }
};

#endif // GAMESTATELOGINAWAITRESPONSE_HPP_INCLUDE
