#include "screenmaker.hpp"

#include "gamestatetitle.hpp"

namespace LoginScreenListeners
{


    class LoginEvent : public GameEventBase
    {
    public:
        LoginEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //this->game->ChangeState(new GameStateQuit(this->game));
        }
    };

    class LoginListener : public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game* game;

    public:
        LoginListener(Game* game) : game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new LoginEvent(this->game));
        }
    };


    class CancelEvent : public GameEventBase
    {
    public:
        CancelEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();
            this->game->ChangeState(new GameStateTitle(this->game));
        }
    };

    class CancelListener : public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game* game;

    public:
        CancelListener(Game* game) : game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new CancelEvent(this->game));
        }
    };

}



GuiScreen* ScreenMakerLogin::MakeScreen()
{
    LoginScreenListeners::CancelListener* cancel_listener = new LoginScreenListeners::CancelListener(this->game);


    ALLEGRO_FONT* text_font = FontService::Instance()->GetFont("title_button");

    Vector2 window_size = Vector2(640, 480);

    Vector2 base_size = Vector2(window_size.x / 3 * 2, window_size.y / 2.5);
    Vector2 base_pos = Vector2((window_size.x - base_size.x) / 2,  (window_size.y - base_size.y) / 2);
    GuiFrame* base_frame = new GuiFrame(base_size, base_pos);
    base_frame->SetBackgroundAlpha(200);


    Vector2 label_size = Vector2(base_size.x / 3, text_font->height + 4);
    Vector2 textbox_size = Vector2(base_size.x / 2, text_font->height + 4);
    int y_pos = 52;

    GuiTextButton* email_label = new GuiTextButton(label_size, Vector2(0, y_pos));
    email_label->SetTextFont(text_font);
    email_label->SetText("Email:");
    email_label->SetTextColor(Color3(255, 255, 255));
    email_label->SetTextAlign(GuiTextButton::ALIGN_RIGHT);
    email_label->SetBackgroundAlpha(0);

    GuiTextButton* password_label = new GuiTextButton(label_size, Vector2(0, y_pos + label_size.y + 4));
    password_label->SetTextFont(text_font);
    password_label->SetText("Password:");
    password_label->SetTextColor(Color3(255, 255, 255));
    password_label->SetTextAlign(GuiTextButton::ALIGN_RIGHT);
    password_label->SetBackgroundAlpha(0);

    GuiTextBox* email_textbox = new GuiTextBox(textbox_size, email_label->GetPosition() + Vector2(label_size.x + 8, 0));
    email_textbox->SetTextFont(text_font);
    email_textbox->SetTextColor(Color3(255, 255, 255));
    email_textbox->SetBackgroundColor(Color3(40, 40, 40));

    GuiTextBox* password_textbox = new GuiTextBox(textbox_size, password_label->GetPosition() + Vector2(label_size.x + 8, 0));
    password_textbox->SetTextFont(text_font);
    password_textbox->SetTextColor(Color3(255, 255, 255));
    password_textbox->SetBackgroundColor(Color3(40, 40, 40));




    Vector2 button_size = Vector2(base_size.x / 4, text_font->height + 4);
    Vector2 button_pos = Vector2((base_size.x - button_size.x) / 2, base_size.y - button_size.y - 4);
    Vector2 pos_adder = Vector2(button_size.x / 3 * 2, 0);

    GuiTextButton* login_button = new GuiTextButton(button_size, button_pos - pos_adder);
    login_button->SetTextFont(text_font);
    login_button->SetTextColor(Color3(255, 255, 255));
    login_button->SetText("Login");
    login_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    GuiTextButton* cancel_button = new GuiTextButton(button_size, button_pos + pos_adder);
    cancel_button->SetTextFont(text_font);
    cancel_button->SetTextColor(Color3(255, 255, 255));
    cancel_button->SetText("Cancel");
    cancel_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    cancel_button->RegisterOnClick(cancel_listener);

    base_frame->AddChild(email_label);
    base_frame->AddChild(password_label);
    base_frame->AddChild(email_textbox);
    base_frame->AddChild(password_textbox);
    base_frame->AddChild(login_button);
    base_frame->AddChild(cancel_button);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->SetGuiId("email", email_textbox);
    screen->SetGuiId("password", password_textbox);


    screen->RegisterListener(cancel_listener);

    return screen;
}
