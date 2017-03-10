#include "screenmaker.hpp"

#include "gamestatetitle.hpp"
#include "gamestateaccountcreation.hpp"
#include "GameNetwork/packet.hpp"

GuiTextButton* CreateAccountCreationWaitButton(int offset, std::string button_text, ALLEGRO_FONT* text_font)
{
    Color3 button_background = Color3(0, 0, 0);
    char button_background_alpha = 180;
    Vector2 button_size = Vector2(200, 26);
    Vector2 button_start_pos = Vector2(640*.7 - button_size.x, 0*.7 + button_size.y) / 2;
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

class AccountCreationButtonEnterListener : public ListenerBase<GuiButtonArgs*>
{
public:
    virtual void Notify(GuiButtonArgs*& args) const
    {
        GuiTextButton* button = static_cast<GuiTextButton*>(args->button);
        button->SetTextColor(Color3(255, 255, 0));
    }
};

class AccountCreationButtonLeaveListener : public ListenerBase<GuiButtonArgs*>
{
public:
    virtual void Notify(GuiButtonArgs*& args) const
    {
        GuiTextButton* button = static_cast<GuiTextButton*>(args->button);
        button->SetTextColor(Color3(255, 255, 255));
    }
};

class DoneEvent : public GameEventBase
{
public:
    DoneEvent(Game* game) : GameEventBase(game) {}

    virtual void HandleEvent()
    {
        this->game->PopScreen();

        ScreenMakerAccountCreation maker(this->game);
        GuiScreen* screen = maker.MakeScreen();
        this->game->PushScreen(screen);
        this->game->ChangeState(new GameStateAccountCreation(this->game));
    }
};

class DoneListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game* game;

public:
    DoneListener(Game* game) : game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        this->game->RegisterEventToQueue(new DoneEvent(this->game));
    }
};

GuiScreen * ScreenMakerAccountCreationResponseWait::MakeScreen()
{
    ALLEGRO_FONT * button_font = FontService::Instance()->GetFont("title_button");

    //listeners
    AccountCreationButtonEnterListener* mouse_enter_listener = new AccountCreationButtonEnterListener();
    AccountCreationButtonLeaveListener* mouse_leave_listener = new AccountCreationButtonLeaveListener();
    DoneListener * done_listener = new DoneListener(this->game);

    //frame
    GuiFrame * waitFrame = new GuiFrame(Vector2(640 * 0.7,480 * 0.7), Vector2(640*0.15, 480*0.15));

    //buttons
    GuiTextButton * information = CreateAccountCreationWaitButton(3, "Waiting for response from server", button_font);
    GuiTextButton * success = CreateAccountCreationWaitButton(7, "Account created!", button_font);
    GuiTextButton * failure = CreateAccountCreationWaitButton(7, "Account creation failed.", button_font);
    GuiTextButton * accept_button = CreateAccountCreationWaitButton(5, "Continue", button_font);

    //setup buttons
    accept_button->RegisterOnMouseEnter(mouse_enter_listener);
    accept_button->RegisterOnMouseLeave(mouse_leave_listener);
    accept_button->RegisterOnClick(done_listener);
    //accept_button->SetVisible(false);
    failure->SetVisible(false);
    success->SetVisible(false);

    //frame setup
    waitFrame->SetBackgroundColor(Color3(0, 50, 0));
    waitFrame->SetBackgroundAlpha( 200);
    waitFrame->AddChild(information);
    waitFrame->AddChild(accept_button);
    waitFrame->AddChild(failure);
    waitFrame->AddChild(success);

    //screen
    GuiScreen* screen = new GuiScreen(waitFrame);

    //screen setup
    screen->RegisterListener(done_listener);
    screen->RegisterListener(mouse_enter_listener);
    screen->RegisterListener(mouse_leave_listener);
    screen->SetGuiId("Confirmation", information);
    screen->SetGuiId("Continue", accept_button);
    screen->SetGuiId("failure", failure);
    screen->SetGuiId("success", success);

    return screen;
}
