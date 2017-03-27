#include "screenmaker.hpp"


#include "gamestatecharacterview.hpp"
#include "gamestatetitle.hpp"
#include "gamestateplaying.hpp"


#include <string>
#include <cstdio>

namespace CharacterViewScreenListeners
{
    class LogoutEvent : public GameEventBase
    {
    public:
        LogoutEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            PacketLogout* packet = new PacketLogout();
            this->game->SendPacket(packet);

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

    class LoginEvent : public GameEventBase
    {
    public:
        LoginEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();

            //ScreenMakerPlaying maker(this->game);
            //GuiScreen* screen = maker.MakeScreen();
            //this->game->PushScreen(screen);
            this->game->ChangeState(new GameStatePlaying(this->game));
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
}







GuiFrame* CreateCharacterFrame(ALLEGRO_FONT* font, CharacterViewScreenListeners::LoginListener* login_listener, Character * player_character)
{
    char statString[100];
    char converter[4];

    GuiFrame* base = new GuiFrame(Vector2(345, 180), Vector2(0, 0));
    base->SetBackgroundColor(Color3(124, 57, 21));

    Color3 color_white = Color3(255, 255, 255);

    GuiTextLabel* character_name = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10));
    character_name->SetText(player_character->GetName());
    character_name->SetTextColor(color_white);
    character_name->SetBackgroundAlpha(255);
    character_name->SetTextFont(font);
    character_name->SetTextAlign(GuiTextLabel::ALIGN_CENTER);

    GuiTextLabel * character_strength = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + font->height));
    snprintf(converter, 4, "%d", player_character->GetStrength());
    strcpy(statString, "Strength:    ");
    strcat(statString, converter);
    character_strength->SetText(statString);
    character_strength->SetTextColor(color_white);
    character_strength->SetBackgroundAlpha(255);
    character_strength->SetTextFont(font);

    GuiTextLabel * character_stamina = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + 2 * font->height));
    snprintf(converter, 4, "%d", player_character->GetEndurance());
    strcpy(statString, "Stamina:    ");
    strcat(statString, converter);
    character_stamina->SetText(statString);
    character_stamina->SetTextColor(color_white);
    character_stamina->SetBackgroundAlpha(255);
    character_stamina->SetTextFont(font);

    GuiTextLabel * character_hitpoints = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + 3 * font->height));
    snprintf(converter, 4, "%d", player_character->GetHealth());
    strcpy(statString, "Hitpoints:    ");
    strcat(statString, converter);
    character_hitpoints->SetText(statString);
    character_hitpoints->SetTextColor(color_white);
    character_hitpoints->SetBackgroundAlpha(255);
    character_hitpoints->SetTextFont(font);

    Vector2 button_size = Vector2(105, font->height);
    Vector2 start = base->GetPosition() + Vector2(105, base->GetSize().y - button_size.y);

    GuiTextButton* login_button = new GuiTextButton(button_size, start);
    login_button->SetText("Login");
    login_button->SetTextColor(color_white);
    login_button->SetTextFont(font);
    login_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    login_button->RegisterOnClick(login_listener);

    GuiTextButton* delete_button = new GuiTextButton(button_size, start + Vector2(button_size.x + 10, 0));
    delete_button->SetText("Delete");
    delete_button->SetTextColor(color_white);
    delete_button->SetTextFont(font);
    delete_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);

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
    CharacterViewScreenListeners::LogoutListener* logout_listener = new CharacterViewScreenListeners::LogoutListener(this->game);
    CharacterViewScreenListeners::LoginListener* login_listener = new CharacterViewScreenListeners::LoginListener(this->game);
    std::vector<GuiFrame*> character_frames;


    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(20, 255, 20));


    ALLEGRO_FONT* font = FontService::Instance()->GetFont("title_button");

    if(!game->GetCharacterList().empty())
    {
        for (unsigned int i = 0; i < game->GetCharacterList().size(); i++)
        {
            character_frames.push_back(CreateCharacterFrame(font, login_listener, game->GetCharacterList()[i]));
            character_frames[i]->SetPosition(Vector2(260, 20 +190*i));
        }
    }

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


    if(!character_frames.empty())
        for(unsigned int i =0; i < character_frames.size(); i++)
            base_frame->AddChild(character_frames[i]);


    base_frame->AddChild(create_char_button);
    base_frame->AddChild(logout_button);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->RegisterListener(logout_listener);
    screen->RegisterListener(login_listener);


    return screen;
}
