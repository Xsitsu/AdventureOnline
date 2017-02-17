#ifndef GAMESTATEINIT_HPP_INCLUDE
#define GAMESTATEINIT_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateInit : public GameStateBase
{
protected:

public:
    GameStateInit(Game* game);

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);

    virtual std::string GetStateName() { return "Init"; }
};

#endif // GAMESTATEINIT_HPP_INCLUDE
