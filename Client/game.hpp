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

class GameEventBase;

class Game
{
friend class GameStateInit;
friend class GameStateServerConnect;
friend class GameStateTitle;
friend class GameStateQuit;
friend class GameStateCharacterView;
friend class GameStateAccountCreation;
friend class GameStateAccountCreationMake;

protected: // Singleton stuff
    static Game* instance;

    Game();
    Game(const Game& copy) {}
    Game& operator=(const Game& rhs) {}
    virtual ~Game();

public:
    static Game* Instance()
    {
        if (instance == NULL)
        {
            instance = new Game();
        }
        return instance;
    }



protected:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* timer;

    bool is_running;

    GameStateBase* state;



    Client* client;

    std::list<GuiScreen*> screen_stack;
    typedef std::list<GuiScreen*>::iterator screen_iter;

    std::list<GameEventBase*> game_event_queue;


    GuiScreen* GetCurrentScreen();
    void DrawScreens();


public:
    void Init();
    void Run();
    void Cleanup();

    void RegisterEventToQueue(GameEventBase* event);

    void ChangeState(GameStateBase* state);
    void PushScreen(GuiScreen* screen);
    void PopScreen();

    bool IsClientConnected() { return this->client->IsConnected(); }

};

class GameEventBase
{
protected:
    Game* game;

public:
    GameEventBase(Game* game) : game(game) {}
    virtual ~GameEventBase() {}

    virtual void HandleEvent() = 0;
};

#endif // GAME_HPP_INCLUDE
