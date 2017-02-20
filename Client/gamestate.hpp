#ifndef GAMESTATE_HPP_INCLUDE
#define GAMESTATE_HPP_INCLUDE

#include <iostream>
#include <string>
#include <list>

class Game;

#include "GameShared/packet.hpp"

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

    virtual void Enter() {}
    virtual void Exit() {}
    virtual void Tick() {}
    virtual void Render() {}

    virtual void HandlePacket(PacketBase* packet) {}

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard) {}
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard) {}
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse) {}
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse) {}
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse) {}

    virtual std::string GetStateName() = 0;
};

#endif // GAMESTATE_HPP_INCLUDE
