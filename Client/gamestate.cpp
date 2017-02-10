#include "gamestate.hpp"

GameStateBase::GameStateBase(Game* game) : game(game)
{}



GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

void GameStateInit::Enter()
{

}

void GameStateInit::Exit()
{

}

void GameStateInit::Tick()
{
    this->game->ChangeState(new GameStateTitle(this->game));
}

void GameStateInit::Render()
{

}

void GameStateInit::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateInit::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{

}

void GameStateInit::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{

}



GameStateTitle::GameStateTitle(Game* game) : GameStateBase(game)
{

}

GameStateTitle::~GameStateTitle()
{

}

void func(const SignalArgs* args)
    { std::cout << "Got a click lol!" << std::endl; }

void GameStateTitle::Enter()
{
    this->game->display = al_create_display(640, 480);
    if (!this->game->display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        throw "break";
    }

    al_register_event_source(this->game->event_queue, al_get_display_event_source(this->game->display));

    al_set_window_position(this->game->display, 100, 100);


    GuiFrame* base_frame;
    std::list<GuiButton*> button_list;

    base_frame = new GuiFrame(Vector2(640 - 40, 480 - 40), Vector2(20, 20));
    base_frame->SetBackgroundColor(Color3(255, 255, 255));

    GuiFrame* frame = new GuiFrame(Vector2(80, 80), Vector2(20, 20));
    frame->SetBackgroundColor(Color3(0, 0, 0));
    frame->SetBackgroundAlpha(100);
    base_frame->AddChild(frame);

    GuiButton* button = new GuiButton(Vector2(200, 60), Vector2(20, 480 - 40 - 60 - 20));
    button->SetBackgroundColor(Color3(235, 20, 20));
    button->SetBackgroundAlpha(180);
    base_frame->AddChild(button);

    button_list.push_back(button);

    button->RegisterOnClick(func);

    GuiScreen* screen = new GuiScreen(base_frame, button_list);
    this->game->PushScreen(screen);
}

void GameStateTitle::Exit()
{
    this->game->PopScreen();
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
