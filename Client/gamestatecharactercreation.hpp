#ifndef GAMESTATECHARACTERCREATION_H
#define GAMESTATECHARACTERCREATION_H

#include "gamestate.hpp"


class GameStateCharacterCreation : public GameStateBase
{
public:
    GameStateCharacterCreation(Game* game);
    ~GameStateCharacterCreation();

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

    virtual std::string GetStateName() { return "CharacterCreation"; }

};

#endif // GAMESTATECHARACTERCREATION_H
