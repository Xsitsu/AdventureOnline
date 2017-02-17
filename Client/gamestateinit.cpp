#include "gamestateinit.hpp"

#include "gamestatetitle.hpp"

GameStateInit::GameStateInit(Game* game) : GameStateBase(game)
{}

void GameStateInit::Enter()
{

}

void GameStateInit::Exit()
{

}

GuiTextButton* CreateTitleButton(int offset, std::string button_text, ALLEGRO_FONT* text_font)
{
    Color3 button_background = Color3(0, 0, 0);
    char button_background_alpha = 180;
    Vector2 button_size = Vector2(200, 26);
    Vector2 button_start_pos = Vector2(640 - button_size.x, 480 + button_size.y) / 2;
    Vector2 button_offset = Vector2(0, 34);


    GuiTextButton* button = new GuiTextButton(button_size, button_start_pos + (button_offset * offset));
    button->SetBackgroundColor(button_background);
    button->SetBackgroundAlpha(button_background_alpha);
    button->SetText(button_text);
    button->SetTextColor(Color3(255, 255, 255));
    button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    button->SetTextFont(text_font);

    return button;
}

void GameStateInit::Tick()
{
    this->game->display = al_create_display(640, 480);
    if (!this->game->display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        throw "break";
    }

    al_register_event_source(this->game->event_queue, al_get_display_event_source(this->game->display));

    al_set_window_position(this->game->display, 100, 100);


    ALLEGRO_FONT* button_font = al_load_font("C:/Windows/Fonts/arial.ttf", 22, 0);
    FontService::Instance()->RegisterFont("title_button", button_font);


    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(255, 255, 255));

    GuiTextButton* button1 = CreateTitleButton(0, "Create Account", button_font);
    base_frame->AddChild(button1);

    GuiTextButton* button2 = CreateTitleButton(1, "Play Game", button_font);
    base_frame->AddChild(button2);

    GuiTextButton* button3 = CreateTitleButton(2, "Options", button_font);
    base_frame->AddChild(button3);

    GuiTextButton* button4 = CreateTitleButton(3, "Quit", button_font);
    base_frame->AddChild(button4);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->SetGuiId("CreateAccount", button1);
    screen->SetGuiId("PlayGame", button2);
    screen->SetGuiId("Options", button3);
    screen->SetGuiId("Quit",  button4);

    this->game->PushScreen(screen);

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
