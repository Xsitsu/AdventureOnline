#include "screenmaker.hpp"


#include "gamestatetitle.hpp"
#include "gamestateaccountcreation.hpp"
#include "GameNetwork/packet.hpp"
#include "gamestateaccountcreationawaitresponse.hpp"



GuiTextButton* CreateAccountCreationButton(int offset, std::string button_text, ALLEGRO_FONT* text_font)
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

GuiTextBox* CreateAccountCreationBox(int offset, std::string button_text, ALLEGRO_FONT* text_font)
{
    Color3 button_background = Color3(0, 0, 0);
    char button_background_alpha = 180;
    Vector2 button_size = Vector2(200, 26);
    Vector2 button_start_pos = Vector2(640*.7 - button_size.x, 0*.7 + button_size.y) / 2;
    Vector2 button_offset = Vector2(0, 34);


    GuiTextBox* text_box = new GuiTextBox(button_size, button_start_pos + (button_offset * offset));
    text_box->SetBackgroundColor(button_background);
    text_box->SetBackgroundAlpha(button_background_alpha);
    text_box->SetText(button_text);
    text_box->SetTextColor(Color3(255, 255, 255));
    text_box->SetTextAlign(GuiTextBox::ALIGN_CENTER);
    text_box->SetTextFont(text_font);

    return text_box;
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

        ScreenMakerTitle maker(this->game);
        GuiScreen* screen = maker.MakeScreen();
        this->game->PushScreen(screen);
        this->game->ChangeState(new GameStateTitle(this->game));
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

class RegisterEvent : public GameEventBase
{
private:
    std::string e_email;
    std::string e_password;
    std::string e_confirmation;

public:
    RegisterEvent(Game* game, GuiTextBox * email, GuiTextBox * password, GuiTextBox * confirmation ) : GameEventBase(game)
    {
        e_email = email->GetText();
        e_password = password->GetText();
        e_confirmation = confirmation->GetText();
    }

    virtual void HandleEvent()
    {
        if (e_password == e_confirmation)
        {
            PacketRegistrationRequest * packet = new PacketRegistrationRequest();
            packet->SetEmail(e_email);
            packet->SetPassword(e_password);

            std::cout << "Packet sent :\t" << packet->GetEmail() << '\t' << packet->GetPassword() << '\t'  << std::endl;
            this->game->SendPacket(packet);            //send out registration request

        //this->game->PopScreen();

            ScreenMakerAccountCreationResponseWait maker(this->game);
            GuiScreen* screen = maker.MakeScreen();
            this->game->PushScreen(screen);
            this->game->ChangeState(new GameStateAccountCreationAwaitResponse(this->game));


        }
        else
        {
            //let the user know that their passwords don't match
        }
    }
};

class RegisterListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game* game;

public:
    RegisterListener(Game* game) : game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        GuiScreen * screen = args->button->GetScreen();
        GuiTextBox * email_box;
        GuiTextBox * password_box;
        GuiTextBox * confirmation_box;

        email_box = static_cast<GuiTextBox*>(screen->GetGuiById("Email"));
        password_box = static_cast<GuiTextBox*>(screen->GetGuiById("Password"));
        confirmation_box = static_cast<GuiTextBox*>(screen->GetGuiById("Confirmation"));

        this->game->RegisterEventToQueue(new RegisterEvent(this->game,email_box, password_box, confirmation_box ));
    }
};





GuiScreen* ScreenMakerAccountCreation::MakeScreen()
{
//font
    ALLEGRO_FONT* button_font = FontService::Instance()->GetFont("title_button");

    //listeners
    AccountCreationButtonEnterListener* mouse_enter_listener = new AccountCreationButtonEnterListener();
    AccountCreationButtonLeaveListener* mouse_leave_listener = new AccountCreationButtonLeaveListener();
    DoneListener * done_listener = new DoneListener(this->game);
    RegisterListener * registration_listener = new RegisterListener(this->game);

    //frame
    GuiFrame * account_creation_frame = new GuiFrame(Vector2(640 * 0.7,480 * 0.7), Vector2(640*0.15, 480*0.15));

    //buttons
    GuiTextButton * user_email_text = CreateAccountCreationButton(0, "Enter Email ",button_font);
    GuiTextButton * user_password_text = CreateAccountCreationButton(2, "Enter Password ",button_font);
    GuiTextButton * user_confirm_text = CreateAccountCreationButton(4, "Confirm Password", button_font);
    GuiTextButton * register_button = CreateAccountCreationButton(7, "Register", button_font);
    GuiTextButton * done_button = CreateAccountCreationButton(8, "Exit", button_font);

    //text boxes
    GuiTextBox * user_email = CreateAccountCreationBox(1, "email@oit.edu", button_font);
    GuiTextBox * user_password = CreateAccountCreationBox(3, "mypassword", button_font);
    GuiTextBox * user_password_confirmation = CreateAccountCreationBox(5, "mypassword", button_font);

    //setup buttons
    register_button->RegisterOnMouseEnter(mouse_enter_listener);
    register_button->RegisterOnMouseLeave(mouse_leave_listener);
    register_button->RegisterOnClick(registration_listener);
    done_button->RegisterOnMouseEnter(mouse_enter_listener);
    done_button->RegisterOnMouseLeave(mouse_leave_listener);
    done_button->RegisterOnClick(done_listener);

    //setup text document
    user_email->SetBackgroundAlpha(80);
    user_password->SetBackgroundAlpha(80);
    user_password_confirmation->SetBackgroundAlpha(80);

    //setup frame
    account_creation_frame->SetBackgroundColor(Color3(255, 155, 100));
    //account_creation_frame->SetBackgroundAlpha(200);
    account_creation_frame->AddChild(user_email_text);
    account_creation_frame->AddChild(user_email);
    account_creation_frame->AddChild(user_password);
    account_creation_frame->AddChild(user_password_text);
    account_creation_frame->AddChild(user_confirm_text);
    account_creation_frame->AddChild(user_password_confirmation);
    account_creation_frame->AddChild(register_button);
    account_creation_frame->AddChild(done_button);

    //screen
    GuiScreen* screen = new GuiScreen(account_creation_frame);

    //setup screen
    screen->RegisterListener(mouse_enter_listener);
    screen->RegisterListener(mouse_leave_listener);
    screen->RegisterListener(done_listener);
    screen->RegisterListener(registration_listener);
    screen->SetGuiId("Email", user_email );
    screen->SetGuiId("Password", user_password );
    screen->SetGuiId("Confirmation", user_password_confirmation );

    return screen;
}
