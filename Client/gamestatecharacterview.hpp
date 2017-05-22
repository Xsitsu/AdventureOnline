#ifndef GAMESTATECHARACTERVIEW_HPP_INCLUDE
#define GAMESTATECHARACTERVIEW_HPP_INCLUDE

#include "gamestate.hpp"
#include "vector"
#include "GameWorld/character.hpp"
class GameStateCharacterView : public GameStateBase
{
public:
    GameStateCharacterView(Game* game);
    ~GameStateCharacterView();

    virtual void Enter();
    virtual void Exit();
    virtual void Tick();
    virtual void Render();

    virtual void HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard);
    virtual void HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual void HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse);
    virtual bool HandlePacket(PacketBase * packet);

    virtual std::string GetStateName() { return "CharacterView"; }

protected:

};

#endif // GAMESTATECHARACTERVIEW_HPP_INCLUDE
