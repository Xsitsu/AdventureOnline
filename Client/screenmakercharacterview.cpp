#include "screenmaker.hpp"


#include "gamestatecharacterview.hpp"
#include "gamestatetitle.hpp"
#include <string>


class LogoutEvent : public GameEventBase
{
public:
    LogoutEvent(Game* game) : GameEventBase(game) {}

    virtual void HandleEvent()
    {
        this->game->PopScreen();

        ScreenMakerTitle maker(this->game);
        GuiScreen* screen = maker.MakeScreen();
        this->game->PushScreen(screen);
        this->game->ChangeState(new GameStateTitle(this->game));
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

class RefreshEvent : public GameEventBase
{
public:
    RefreshEvent(Game * game): GameEventBase(game){}

    virtual void HandleEvent()
    {
        PacketDataRequest * datarequest = new PacketDataRequest();
        datarequest->SetRequest(PacketDataRequest::USER_CHARACTERS_DATA);
        game->SendPacket(datarequest);
    }
};

class RefreshListener : public ListenerBase<GuiButtonArgs*>
{
protected:
    Game * game;

public:
    RefreshListener(Game * game): game(game) {}

    virtual void Notify(GuiButtonArgs*& args) const
    {
        this->game->RegisterEventToQueue(new RefreshEvent(this->game));
    }
};



GuiFrame* CreateCharacterFrame(ALLEGRO_FONT* font, ALLEGRO_BITMAP * icon)
{
    GuiFrame* base = new GuiFrame(Vector2(345, 180), Vector2(0, 0));
    base->SetBackgroundColor(Color3(124, 57, 21));

    GuiFrame* character_image_frame = new GuiImageFrame(Vector2(120 - 20, 180 - 20), Vector2(10, 10), icon);
    character_image_frame->SetBackgroundColor(Color3(0, 0, 0));

    Color3 color_white = Color3(255, 255, 255);

    GuiTextButton* character_name = new GuiTextButton(Vector2(220, font->height), Vector2(115, 10));
    character_name->SetText("Character");
    character_name->SetTextColor(color_white);
    character_name->SetBackgroundAlpha(255);
    character_name->SetTextFont(font);
    character_name->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    GuiTextButton * character_strength = new GuiTextButton(Vector2(220, font->height), Vector2(115, 10 + font->height));
    character_strength->SetText("Strength:    5" );
    character_strength->SetTextColor(color_white);
    character_strength->SetBackgroundAlpha(255);
    character_strength->SetTextFont(font);

    GuiTextButton * character_stamina = new GuiTextButton(Vector2(220, font->height), Vector2(115, 10 + 2 * font->height));
    character_stamina->SetText("Stamina:    5");
    character_stamina->SetTextColor(color_white);
    character_stamina->SetBackgroundAlpha(255);
    character_stamina->SetTextFont(font);

    GuiTextButton * character_hitpoints = new GuiTextButton(Vector2(220, font->height), Vector2(115, 10 + 3 * font->height));
    character_hitpoints->SetText("Hitpoints:    50");
    character_hitpoints->SetTextColor(color_white);
    character_hitpoints->SetBackgroundAlpha(255);
    character_hitpoints->SetTextFont(font);

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
    base->AddChild(character_hitpoints);
    base->AddChild(character_stamina);
    base->AddChild(character_strength);

    return base;
}






GuiScreen* ScreenMakerCharacterView::MakeScreen()
{
    LogoutListener * logout_listener = new LogoutListener(this->game);
    RefreshListener * refresh_listener = new RefreshListener(this->game);
    ALLEGRO_BITMAP * icon, * icon2;
    //bool error_check;

    al_init_image_addon();
    //std::cout << "Error check code:"  << error_check << std::endl;
    icon = al_load_bitmap("B:/AdventureOnline/AdventureOnline/Client/Images/Asdfstuff-asdf-movie-30876901-200-200.jpg");
    icon2 = al_load_bitmap("B:/AdventureOnline/AdventureOnline/Client/Images/Asdfstuff-asdf-movie-30876901-200-200.jpg");

    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(20, 255, 20));


    ALLEGRO_FONT* font = FontService::Instance()->GetFont("title_button");

    GuiFrame* character_frame = CreateCharacterFrame(font, icon);
    character_frame->SetPosition(Vector2(260, 20));

    GuiFrame* character_frame2 = CreateCharacterFrame(font, icon2);
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

    GuiTextButton* refresh_button = new GuiTextButton(button_size, Vector2(60 + button_size.x + button_size.x, 480 - 48 - 20));
    refresh_button->SetTextFont(font);
    refresh_button->SetTextColor(Color3(255, 255, 255));
    refresh_button->SetText("Refresh");
    refresh_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    refresh_button->RegisterOnClick(refresh_listener);



    base_frame->AddChild(character_frame);
    base_frame->AddChild(character_frame2);
    base_frame->AddChild(refresh_button);
    base_frame->AddChild(create_char_button);
    base_frame->AddChild(logout_button);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->RegisterListener(logout_listener);
    screen->RegisterListener(refresh_listener);

    return screen;
}
