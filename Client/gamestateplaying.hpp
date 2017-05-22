#ifndef GAMESTATEPLAYING_HPP_INCLUDE
#define GAMESTATEPLAYING_HPP_INCLUDE

#include "gamestate.hpp"

class GameStatePlaying : public GameStateBase
{
protected:

public:
    GameStatePlaying(Game* game);

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual bool HandlePacket(PacketBase* packet);

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);

    virtual std::string GetStateName() { return "Playing"; }
};

#endif // GAMESTATEPLAYING_HPP_INCLUDE
