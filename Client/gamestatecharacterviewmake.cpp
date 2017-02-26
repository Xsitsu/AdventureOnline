#include "gamestatecharacterviewmake.hpp"

#include "gamestatecharacterview.hpp"
#include "gamestatetitlemake.hpp"



class LogoutEvent : public GameEventBase
{
public:
    LogoutEvent(Game* game) : GameEventBase(game) {}

    virtual void HandleEvent()
    {
        this->game->PopScreen();
        this->game->ChangeState(new GameStateTitleMake(this->game));
    }
};

class LogoutListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game* game;

public:
    LogoutListener(Game* game) : game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        this->game->RegisterEventToQueue(new LogoutEvent(this->game));
    }
};






GuiFrame* CreateCharacterFrame(ALLEGRO_FONT* font)
{
    GuiFrame* base = new GuiFrame(Vector2(345, 180), Vector2(0, 0));
    base->SetBackgroundColor(Color3(124, 57, 21));

    GuiFrame* character_image_frame = new GuiFrame(Vector2(120 - 20, 180 - 20), Vector2(10, 10));
    character_image_frame->SetBackgroundColor(Color3(0, 0, 0));

    Color3 color_white = Color3(255, 255, 255);

    GuiTextButton* character_name = new GuiTextButton(Vector2(220, font->height), Vector2(115, 10));
    character_name->SetText("Character");
    character_name->SetTextColor(color_white);
    character_name->SetBackgroundAlpha(255);
    character_name->SetTextFont(font);
    character_name->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    Vector2 button_size = Vector2(105, font->height);
    Vector2 start = character_image_frame->GetPosition() + Vector2(105, character_image_frame->GetSize().y - button_size.y);

    GuiTextButton* login_button = new GuiTextButton(button_size, start);
    login_button->SetText("Login");
    login_button->SetTextColor(color_white);
    login_button->SetTextFont(font);
    login_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    GuiTextButton* delete_button = new GuiTextButton(button_size, start + Vector2(button_size.x + 10, 0));
    delete_button->SetText("Delete");
    delete_button->SetTextColor(color_white);
    delete_button->SetTextFont(font);
    delete_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    base->AddChild(character_image_frame);
    base->AddChild(character_name);
    base->AddChild(login_button);
    base->AddChild(delete_button);

    return base;
}

void GameStateCharacterViewMake::Enter()
{
    LogoutListener* logout_listener = new LogoutListener(this->game);


    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(20, 255, 20));


    ALLEGRO_FONT* font = FontService::Instance()->GetFont("title_button");

    GuiFrame* character_frame = CreateCharacterFrame(font);
    character_frame->SetPosition(Vector2(260, 20));

    GuiFrame* character_frame2 = CreateCharacterFrame(font);
    character_frame2->SetPosition(Vector2(260, 20 + 180 + 10));



    Vector2 button_size = Vector2(160, 48);

    GuiTextButton* create_char_button = new GuiTextButton(button_size, Vector2(20, 480 - 48 - 20));
    create_char_button->SetTextFont(font);
    create_char_button->SetTextColor(Color3(255, 255, 255));
    create_char_button->SetText("Create");
    create_char_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    GuiTextButton* logout_button = new GuiTextButton(button_size, Vector2(20 + button_size.x + 20, 480 - 48 - 20));
    logout_button->SetTextFont(font);
    logout_button->SetTextColor(Color3(255, 255, 255));
    logout_button->SetText("Logout");
    logout_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    logout_button->RegisterOnClick(logout_listener);




    base_frame->AddChild(character_frame);
    base_frame->AddChild(character_frame2);

    base_frame->AddChild(create_char_button);
    base_frame->AddChild(logout_button);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->RegisterListener(logout_listener);

    this->game->PushScreen(screen);

    this->game->ChangeState(new GameStateCharacterView(this->game));

}