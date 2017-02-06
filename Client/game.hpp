#ifndef GAME_HPP_INCLUDE
#define GAME_HPP_INCLUDE

#include <iostream>

#include "allegro5/allegro.h"

class GameStateBase;

#include "GameShared/packet.hpp"
#include "client.hpp"
#include "gamestate.hpp"

class Game
{
friend class GameStateInit;
friend class GameStateTitle;

protected:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* timer;

    bool is_running;

    GameStateBase* state;

    void ChangeState(GameStateBase* state);

    Client* client;

public:
    Game();
    ~Game();

    void Init();
    void Run();

};
#endif // GAME_HPP_INCLUDE
