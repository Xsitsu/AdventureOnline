#include "gamestatetitlemake.hpp"

#include "gamestatetitle.hpp"
#include "gamestatequit.hpp"
#include "gamestatecharacterviewmake.hpp"



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


class OptionsEvent : public GameEventBase
{
public:
    OptionsEvent(Game* game) : GameEventBase(game) {}

    virtual void HandleEvent()
    {
        this->game->PopScreen();
        this->game->ChangeState(new GameStateCharacterViewMake(this->game));
    }
};

class OptionsListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game* game;

public:
    OptionsListener(Game* game) : game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        this->game->RegisterEventToQueue(new OptionsEvent(this->game));
    }
};






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

void GameStateTitleMake::Enter()
{
    ALLEGRO_FONT* button_font = FontService::Instance()->GetFont("title_button");

    TitleButtonEnterListener* mouse_enter_listener = new TitleButtonEnterListener();
    TitleButtonLeaveListener* mouse_leave_listener = new TitleButtonLeaveListener();
    GameQuitListener* game_quit_listener = new GameQuitListener(this->game);
    OptionsListener* option_listener = new OptionsListener(this->game);

    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(255, 255, 255));

    GuiTextButton* button1 = CreateTitleButton(0, "Create Account", button_font);
    button1->RegisterOnMouseEnter(mouse_enter_listener);
    button1->RegisterOnMouseLeave(mouse_leave_listener);
    base_frame->AddChild(button1);

    GuiTextButton* button2 = CreateTitleButton(1, "Play Game", button_font);
    button2->RegisterOnMouseEnter(mouse_enter_listener);
    button2->RegisterOnMouseLeave(mouse_leave_listener);
    base_frame->AddChild(button2);

    GuiTextButton* button3 = CreateTitleButton(2, "Options", button_font);
    button3->RegisterOnMouseEnter(mouse_enter_listener);
    button3->RegisterOnMouseLeave(mouse_leave_listener);
    button3->RegisterOnClick(option_listener);
    base_frame->AddChild(button3);

    GuiTextButton* button4 = CreateTitleButton(3, "Quit", button_font);
    button4->RegisterOnMouseEnter(mouse_enter_listener);
    button4->RegisterOnMouseLeave(mouse_leave_listener);
    button4->RegisterOnClick(game_quit_listener);
    base_frame->AddChild(button4);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->RegisterListener(mouse_enter_listener);
    screen->RegisterListener(mouse_leave_listener);
    screen->RegisterListener(game_quit_listener);
    screen->RegisterListener(option_listener);
    //screen->SetGuiId("CreateAccount", button1);
    //screen->SetGuiId("PlayGame", button2);
    //screen->SetGuiId("Options", button3);
    //screen->SetGuiId("Quit",  button4);

    this->game->PushScreen(screen);

    this->game->ChangeState(new GameStateTitle(this->game));
}
