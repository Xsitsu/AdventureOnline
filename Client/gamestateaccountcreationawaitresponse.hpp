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

    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);


};

#endif // GAMESTATEACCOUNTCREATIONAWAITRESPONSE_H
