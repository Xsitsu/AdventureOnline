#ifndef GAME_HPP_INCLUDE
#define GAME_HPP_INCLUDE

#include <iostream>
#include <stack>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class GameStateBase;

#include "GameShared/packet.hpp"
#include "client.hpp"
#include "gamestate.hpp"

#include "guiscreen.hpp"

#include "fontservice.hpp"
#include "guiselectionservice.hpp"

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

    std::list<GuiScreen*> screen_stack;
    typedef std::list<GuiScreen*>::iterator screen_iter;

    void PushScreen(GuiScreen* screen);
    void PopScreen();
    void DrawScreens();
    GuiScreen* GetCurrentScreen();

public:
    Game();
    ~Game();

    void Init();
    void Run();

};
#endif // GAME_HPP_INCLUDE
