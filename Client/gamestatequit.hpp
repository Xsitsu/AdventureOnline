#ifndef GAMESTATEQUIT_HPP_INCLUDE
#define GAMESTATEQUIT_HPP_INCLUDE

#include "gamestate.hpp"

class GameStateQuit : public GameStateBase
{
protected:

public:
    GameStateQuit(Game* game);
    ~GameStateQuit();

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);

    virtual std::string GetStateName() { return "Quit"; }
};

#endif // GAMESTATEQUIT_HPP_INCLUDE
