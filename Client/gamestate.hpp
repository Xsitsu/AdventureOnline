#ifndef GAMESTATE_HPP_INCLUDE
#define GAMESTATE_HPP_INCLUDE

#include <iostream>
#include <string>
#include <list>

class Game;

#include "game.hpp"

#include "guiframe.hpp"
#include "guitextbutton.hpp"
#include "guitextbox.hpp"
#include "guiscreen.hpp"
#include "GameShared/vector2.hpp"

#include "color3.hpp"

#include "allegro5/allegro.h"

class GameStateBase
{
protected:
    Game* game;

public:
    GameStateBase(Game* game) : game(game) {}
    virtual ~GameStateBase() {}

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Tick() = 0;
    virtual void Render() = 0;

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) = 0;
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard) = 0;
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse) = 0;
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse) = 0;
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse) = 0;

    virtual std::string GetStateName() = 0;
};

#endif // GAMESTATE_HPP_INCLUDE
