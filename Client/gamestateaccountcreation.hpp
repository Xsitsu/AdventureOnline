#ifndef GAMESTATEACCOUNTCREATION_H
#define GAMESTATEACCOUNTCREATION_H

#include "gamestate.hpp"


class GameStateAccountCreation : public GameStateBase
{
    public:
        GameStateAccountCreation(Game * game);
        virtual ~GameStateAccountCreation();

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandlePacket(PacketBase* packet);

    virtual std::string GetStateName() { return "AccountCreation"; }
};

#endif // GAMESTATEACCOUNTCREATION_H
