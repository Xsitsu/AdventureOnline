#ifndef GAMESTATETITLE_HPP_INCLUDE
#define GAMESTATETITLE_HPP_INCLUDE

#include "gamestate.hpp"
#include "gamestatequit.hpp"

class TitleButtonEnterListener : public ListenerBase<GuiButtonArgs*>
{
public:
    virtual void Notify(GuiButtonArgs*& args) const
    {
        GuiTextButton* button = static_cast<GuiTextButton*>(args->button);
        button->SetTextColor(Color3(255, 255, 0));
    }
};

class TitleButtonLeaveListener : public ListenerBase<GuiButtonArgs*>
{
public:
    virtual void Notify(GuiButtonArgs*& args) const
    {
        GuiTextButton* button = static_cast<GuiTextButton*>(args->button);
        button->SetTextColor(Color3(255, 255, 255));
    }
};


class GameQuitEvent : public GameEventBase
{
public:
    GameQuitEvent(Game* game) : GameEventBase(game) {}

    virtual void HandleEvent()
    {
        this->game->ChangeState(new GameStateQuit(this->game));
    }
};

class GameQuitListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game* game;

public:
    GameQuitListener(Game* game) : game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        this->game->RegisterEventToQueue(new GameQuitEvent(this->game));
    }
};




class GameStateTitle : public GameStateBase
{
protected:
    ListenerBase<GuiButtonArgs*>* mouse_enter_listener;
    ListenerBase<GuiButtonArgs*>* mouse_leave_listener;
    ListenerBase<GuiButtonArgs*>* game_quit_listener;

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
