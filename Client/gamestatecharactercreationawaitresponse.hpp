
#ifndef GAMESTATECHARACTERCREATIONAWAITRESPONSE_H
#define GAMESTATECHARACTERCREATIONAWAITRESPONSE_H

#include "gamestate.hpp"


class GameStateCharacterCreationAwaitResponse : public GameStateBase
{
public:

    GameStateCharacterCreationAwaitResponse(Game* game) : GameStateBase(game) {}

    virtual void Render();

    virtual bool HandlePacket(PacketBase* packet);

    virtual std::string GetStateName() { return "AccountCreationAwaitResponse"; }

    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);


};

#endif // GAMESTATEACCOUNTCREATIONAWAITRESPONSE_H
