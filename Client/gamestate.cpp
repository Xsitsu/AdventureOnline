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



GameStateTitle::GameStateTitle(Game* game) : GameStateBase(game)
{
    this->base_frame = new GuiFrame(Vector2(640 - 40, 480 - 40), Vector2(20, 20));
    this->base_frame->SetBackgroundColor(Color3(255, 255, 255));

    GuiFrame* frame = new GuiFrame(Vector2(80, 80), Vector2(20, 20));
    frame->SetBackgroundColor(Color3(0, 0, 0));
    frame->SetBackgroundAlpha(100);
    this->base_frame->AddChild(frame);

    GuiButton* button = new GuiButton(Vector2(200, 60), Vector2(20, 480 - 40 - 60 - 20));
    button->SetBackgroundColor(Color3(235, 20, 20));
    button->SetBackgroundAlpha(180);
    this->base_frame->AddChild(button);
}

GameStateTitle::~GameStateTitle()
{
    delete this->base_frame;
}

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
}

void GameStateTitle::Exit()
{

}

void GameStateTitle::Tick()
{

}

void GameStateTitle::Render()
{
    this->base_frame->Draw();
}
