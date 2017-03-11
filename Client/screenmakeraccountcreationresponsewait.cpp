#include "screenmaker.hpp"

#include "gamestatetitle.hpp"
#include "gamestateaccountcreation.hpp"
#include "GameNetwork/packet.hpp"

namespace AccountCreationAwaitListeners
{

    GuiTextButton* CreateAccountCreationWaitButton(int offset, std::string button_text, ALLEGRO_FONT* text_font)
    {
        Color3 button_background = Color3(0, 0, 0);
        char button_background_alpha = 180;
        Vector2 button_size = Vector2(200, 26);
        Vector2 button_start_pos = Vector2(640*.5 - button_size.x, 0*.5 + button_size.y) / 2;
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

    class ContinueAccountCreationEvent : public GameEventBase
    {
    public:
        ContinueAccountCreationEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();

//            ScreenMakerAccountCreation maker(this->game);
//            GuiScreen * screen = maker.MakeScreen();
//            this->game->PushScreen(screen);
            this->game->ChangeState(new GameStateAccountCreation(this->game));
        }
    };

    class ContinueAccountCreationListener : public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game* game;

    public:
        ContinueAccountCreationListener(Game* game) : game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new AccountCreationAwaitListeners::ContinueAccountCreationEvent(this->game));
        }
    };
}


GuiScreen * ScreenMakerAccountCreationResponseWait::MakeScreen()
{
    ALLEGRO_FONT * button_font = FontService::Instance()->GetFont("title_button");

    //listeners
    AccountCreationAwaitListeners::AccountCreationButtonEnterListener* mouse_enter_listener = new AccountCreationAwaitListeners::AccountCreationButtonEnterListener();
    AccountCreationAwaitListeners::AccountCreationButtonLeaveListener* mouse_leave_listener = new AccountCreationAwaitListeners::AccountCreationButtonLeaveListener();
    AccountCreationAwaitListeners::ContinueAccountCreationListener * done_listener = new AccountCreationAwaitListeners::ContinueAccountCreationListener(this->game);

    //frame
    GuiFrame * waitFrame = new GuiFrame(Vector2(640 * 0.50,480 * 0.50), Vector2(640*0.25, 480*0.25));

    //buttons
    GuiTextButton * information = AccountCreationAwaitListeners::CreateAccountCreationWaitButton(3, "Waiting for response from server", button_font);
    //GuiTextButton * success = AccountCreationAwaitListeners::CreateAccountCreationWaitButton(7, "Account created!", button_font);
    //GuiTextButton * failure = AccountCreationAwaitListeners::CreateAccountCreationWaitButton(7, "Account creation failed.", button_font);
    GuiTextButton * accept_button = AccountCreationAwaitListeners::CreateAccountCreationWaitButton(5, "Continue", button_font);

    //setup buttons
    accept_button->RegisterOnMouseEnter(mouse_enter_listener);
    accept_button->RegisterOnMouseLeave(mouse_leave_listener);
    accept_button->RegisterOnClick(done_listener);
    information->SetBackgroundAlpha(0);
    //accept_button->SetVisible(false);
    //failure->SetVisible(false);
    //success->SetVisible(false);

    //frame setup
    waitFrame->SetBackgroundColor(Color3(0, 50, 0));
    //waitFrame->SetBackgroundAlpha( 200);
    waitFrame->AddChild(information);
    waitFrame->AddChild(accept_button);
    //waitFrame->AddChild(failure);
    //waitFrame->AddChild(success);

    //screen
    GuiScreen* screen = new GuiScreen(waitFrame);

    //screen setup
    screen->RegisterListener(done_listener);
    screen->RegisterListener(mouse_enter_listener);
    screen->RegisterListener(mouse_leave_listener);
    screen->SetGuiId("Confirmation", information);
    screen->SetGuiId("Continue", accept_button);
    //screen->SetGuiId("failure", failure);
    //screen->SetGuiId("success", success);

    return screen;
}
