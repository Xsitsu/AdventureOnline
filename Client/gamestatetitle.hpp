#ifndef GAMESTATETITLE_HPP_INCLUDE
#define GAMESTATETITLE_HPP_INCLUDE

#include "gamestate.hpp"
#include "gamestatequit.hpp"


class GameStateTitle : public GameStateBase
{
public:
    GameStateTitle(Game* game);
    ~GameStateTitle();

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);

    virtual std::string GetStateName() { return "Title"; }
};

#endif // GAMESTATETITLE_HPP_INCLUDE
