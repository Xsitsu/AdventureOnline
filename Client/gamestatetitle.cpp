#include "gamestate.hpp"

GameStateTitle::GameStateTitle(Game* game) : GameStateBase(game)
{

}

GameStateTitle::~GameStateTitle()
{

}

void clickFunc(const SignalArgs* args)
{
    if (const SignalArgsGuiTextButton* aargs = dynamic_cast<const SignalArgsGuiTextButton*>(args))
    {
        //aargs->button->SetText("Button was clicked!");
        //aargs->button->GetParent()->RemoveChild(aargs->button);
    }
    else if (const SignalArgsGuiTextBox* aargs = dynamic_cast<const SignalArgsGuiTextBox*>(args))
    {
        aargs->text_box->SetText("");
    }
}

void mouseEnterFunc(const SignalArgs* args)
{
    if (const SignalArgsGuiTextButton* aargs = dynamic_cast<const SignalArgsGuiTextButton*>(args))
    {
        aargs->button->SetTextColor(Color3(255, 255, 0));
    }
    else if (const SignalArgsGuiTextBox* aargs = dynamic_cast<const SignalArgsGuiTextBox*>(args))
    {
        aargs->text_box->SetBackgroundAlpha(255);
    }
}

void mouseLeaveFunc(const SignalArgs* args)
{
    if (const SignalArgsGuiTextButton* aargs = dynamic_cast<const SignalArgsGuiTextButton*>(args))
    {
        aargs->button->SetTextColor(Color3(255, 255, 255));
    }
    else if (const SignalArgsGuiTextBox* aargs = dynamic_cast<const SignalArgsGuiTextBox*>(args))
    {
        aargs->text_box->SetBackgroundAlpha(180);
    }
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
    button->RegisterOnClick(clickFunc);
    button->RegisterOnMouseEnter(mouseEnterFunc);
    button->RegisterOnMouseLeave(mouseLeaveFunc);

    return button;
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


    ALLEGRO_FONT* button_font = al_load_font("C:/Windows/Fonts/arial.ttf", 22, 0);
    FontService::Instance()->RegisterFont("title_button", button_font);


    GuiFrame* base_frame;

    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(255, 255, 255));

    base_frame->AddChild(CreateTitleButton(0, "Create Account", button_font));
    base_frame->AddChild(CreateTitleButton(1, "Play Game", button_font));
    base_frame->AddChild(CreateTitleButton(2, "Options", button_font));
    base_frame->AddChild(CreateTitleButton(3, "Quit", button_font));

    GuiScreen* screen = new GuiScreen(base_frame);
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
