#ifndef GAMESTATEACCOUNTCREATIONAWAITRESPONSE_H
#define GAMESTATEACCOUNTCREATIONAWAITRESPONSE_H

#include "gamestate.hpp"


class GameStateAccountCreationAwaitResponse : public GameStateBase
{
public:

    GameStateAccountCreationAwaitResponse(Game* game) : GameStateBase(game) {}

    virtual void Render();

    virtual void HandlePacket(PacketBase* packet);

    virtual std::string GetStateName() { return "AccountCreationAwaitResponse"; }
};

#endif // GAMESTATEACCOUNTCREATIONAWAITRESPONSE_H
