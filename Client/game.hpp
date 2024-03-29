#ifndef GAME_HPP_INCLUDE
#define GAME_HPP_INCLUDE

#include <iostream>
#include <stack>
#include <vector>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class GameStateBase;

#include "GameNetwork/packet.hpp"
#include "client.hpp"
#include "gamestate.hpp"

#include "GameGui/guiscreen.hpp"

#include "fontservice.hpp"
#include "GameGui/guiselectionservice.hpp"

#include "GameWorld/character.hpp"
#include "GameWorld/map.hpp"

#include "bitmapservice.hpp"

class GameEventBase;

class Game
{
friend class GameStateInit;
friend class GameStateServerConnect;
friend class GameStateTitle;
friend class GameStateQuit;
friend class GameStateCharacterView;
friend class GameStateAccountCreation;
friend class GameStateLoginAwaitResponse;
friend class GameStateAccountCreationAwaitResponse;
friend class GameStatePlaying;
friend class GameStateCharacterCreation;
friend class GameStateCharacterCreationAwaitResponse;

protected: // Singleton stuff
    static Game* instance;

    Game();
    Game(const Game& copy) {}
    Game& operator=(const Game& rhs) { return *this; }
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

    Map* current_map;
    Character* current_character;
    std::vector<Character*> character_list;



    void DrawScreens();


public:
    void Init();
    void Run();
    void Cleanup();

    void RegisterEventToQueue(GameEventBase* event);

    void ChangeState(GameStateBase* state);
    void PushScreen(GuiScreen* screen);
    void PopScreen();
    GuiScreen* GetCurrentScreen();

    bool IsClientConnected() { return this->client->IsConnected(); }
    void SendPacket(PacketBase* packet) { this->client->SendPacket(packet); }

    void LoginAsCharacter(Character* character);
    std::vector<Character*> GetCharacterList() const;
    void ClearCharacterList();
    Character * GetCurrentCharacter() { return current_character; }
    void SetCurrentCharacter( Character * val ) { current_character = val; }


    void LoadResourceFile(std::string fname, BitmapService::BitmapSets set_id, ALLEGRO_COLOR mask_color);
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
