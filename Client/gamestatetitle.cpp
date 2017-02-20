#include "gamestatetitle.hpp"

#include "gamestatequit.hpp"

GameStateTitle::GameStateTitle(Game* game) : GameStateBase(game)
{
    this->mouse_enter_listener = new TitleButtonEnterListener();
    this->mouse_leave_listener = new TitleButtonLeaveListener();
    this->game_quit_listener = new GameQuitListener(this->game);
}

GameStateTitle::~GameStateTitle()
{
    delete this->mouse_enter_listener;
    delete this->mouse_leave_listener;
    delete this->game_quit_listener;
}

void GameStateTitle::Enter()
{
    GuiScreen* screen = this->game->GetCurrentScreen();
    GuiTextButton* button;

    button = static_cast<GuiTextButton*>(screen->GetGuiById("CreateAccount"));
    button->RegisterOnMouseEnter(mouse_enter_listener);
    button->RegisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("PlayGame"));
    button->RegisterOnMouseEnter(mouse_enter_listener);
    button->RegisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("Options"));
    button->RegisterOnMouseEnter(mouse_enter_listener);
    button->RegisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("Quit"));
    button->RegisterOnMouseEnter(mouse_enter_listener);
    button->RegisterOnMouseLeave(mouse_leave_listener);
    button->RegisterOnClick(game_quit_listener);


}

void GameStateTitle::Exit()
{
    GuiScreen* screen = this->game->GetCurrentScreen();
    GuiTextButton* button;

    button = static_cast<GuiTextButton*>(screen->GetGuiById("CreateAccount"));
    button->UnregisterOnMouseEnter(mouse_enter_listener);
    button->UnregisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("PlayGame"));
    button->UnregisterOnMouseEnter(mouse_enter_listener);
    button->UnregisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("Options"));
    button->UnregisterOnMouseEnter(mouse_enter_listener);
    button->UnregisterOnMouseLeave(mouse_leave_listener);

    button = static_cast<GuiTextButton*>(screen->GetGuiById("Quit"));
    button->UnregisterOnMouseEnter(mouse_enter_listener);
    button->UnregisterOnMouseLeave(mouse_leave_listener);
    button->UnregisterOnClick(game_quit_listener);
}

void GameStateTitle::Tick()
{

}

void GameStateTitle::Render()
{
    this->game->DrawScreens();
}

void GameStateTitle::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateTitle::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateTitle::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateTitle::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateTitle::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
