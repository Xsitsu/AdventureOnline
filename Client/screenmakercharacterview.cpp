#include "screenmaker.hpp"


#include "gamestatecharacterview.hpp"
#include "gamestatetitle.hpp"
#include "gamestateplaying.hpp"
#include "gamestatecharactercreation.hpp"


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

            this->game->ClearCharacterList();

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
        unsigned int slot_num;

    public:
        LoginListener(Game* game) : game(game) {}
        void SetSlotNumber(unsigned int slot_num) { this->slot_num = slot_num; }

        virtual void Notify(GuiButtonArgs*& args) const
        {
            unsigned int base = 0;
            unsigned int slot = base + this->slot_num;

            std::vector<Character*> character_list = this->game->GetCharacterList();
            if (character_list.size() > slot)
            {
                Character* character = character_list[slot];
                if (character)
                {
                    this->game->LoginAsCharacter(character);
                    this->game->RegisterEventToQueue(new LoginEvent(this->game));
                }
            }

        }
    };

    class CreateCharacterEvent : public GameEventBase
    {
    public:
        CreateCharacterEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();

            SreenMakerCharacterCreation maker(this->game);
            GuiScreen* screen = maker.MakeScreen();
            this->game->PushScreen(screen);
            this->game->ChangeState(new GameStateCharacterCreation(this->game));
        }
    };

    class CreateCharacterListener : public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game* game;

    public:
        CreateCharacterListener(Game* game) : game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new CreateCharacterEvent(this->game));
        }
    };
}







GuiFrame* CreateCharacterFrame(ALLEGRO_FONT* font)
{
    GuiFrame* base = new GuiFrame(Vector2(345, 180), Vector2(0, 0));
    base->SetBackgroundColor(Color3(124, 57, 21));

    GuiFrame* character_draw_area = new GuiFrame(Vector2(120 - 20, 180 - 20), Vector2(10, 10));
    character_draw_area->SetBackgroundColor(Color3(0, 0, 0));
    character_draw_area->SetBackgroundAlpha(255);

    Color3 color_white = Color3(255, 255, 255);

    GuiTextLabel* character_name = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10));
    character_name->SetText("Character Name");
    character_name->SetTextColor(color_white);
    character_name->SetBackgroundAlpha(255);
    character_name->SetTextFont(font);
    character_name->SetTextAlign(GuiTextLabel::ALIGN_CENTER);

    GuiTextLabel * character_strength = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + font->height));
    character_strength->SetText("STR:");
    character_strength->SetTextColor(color_white);
    character_strength->SetBackgroundAlpha(255);
    character_strength->SetTextFont(font);

    GuiTextLabel * character_stamina = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + 2 * font->height));
    character_stamina->SetText("END:");
    character_stamina->SetTextColor(color_white);
    character_stamina->SetBackgroundAlpha(255);
    character_stamina->SetTextFont(font);

    GuiTextLabel * character_hitpoints = new GuiTextLabel(Vector2(220, font->height), Vector2(115, 10 + 3 * font->height));
    character_hitpoints->SetText("HP:");
    character_hitpoints->SetTextColor(color_white);
    character_hitpoints->SetBackgroundAlpha(255);
    character_hitpoints->SetTextFont(font);

    Vector2 button_size = Vector2(105, font->height);
    Vector2 start = character_draw_area->GetPosition() + Vector2(105, character_draw_area->GetSize().y - button_size.y);

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

    base->AddChild(character_name);
    base->AddChild(login_button);
    base->AddChild(delete_button);
    base->AddChild(character_hitpoints);
    base->AddChild(character_stamina);
    base->AddChild(character_strength);
    base->AddChild(character_draw_area);

    base->SetGuiId("character_name", character_name);
    base->SetGuiId("login_button", login_button);
    base->SetGuiId("delete_button", delete_button);
    base->SetGuiId("character_draw_area", character_draw_area);

    return base;
}






GuiScreen* ScreenMakerCharacterView::MakeScreen()
{
    ALLEGRO_FONT* font = FontService::Instance()->GetFont("title_button");

    CharacterViewScreenListeners::LogoutListener* logout_listener = new CharacterViewScreenListeners::LogoutListener(this->game);
    CharacterViewScreenListeners::LoginListener* login_listener_1 = new CharacterViewScreenListeners::LoginListener(this->game);
    CharacterViewScreenListeners::LoginListener* login_listener_2 = new CharacterViewScreenListeners::LoginListener(this->game);
    CharacterViewScreenListeners::CreateCharacterListener * create_listener = new CharacterViewScreenListeners::CreateCharacterListener(this->game);

    login_listener_1->SetSlotNumber(0);
    login_listener_2->SetSlotNumber(1);

    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(20, 255, 20));

    Vector2 button_size = Vector2(160, 48);

    GuiTextButton* create_char_button = new GuiTextButton(button_size, Vector2(20, 480 - 48 - 20));
    create_char_button->SetTextFont(font);
    create_char_button->SetTextColor(Color3(255, 255, 255));
    create_char_button->SetText("Create");
    create_char_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    create_char_button->RegisterOnClick(create_listener);

    GuiTextButton* logout_button = new GuiTextButton(button_size, Vector2(20 + button_size.x + 20, 480 - 48 - 20));
    logout_button->SetTextFont(font);
    logout_button->SetTextColor(Color3(255, 255, 255));
    logout_button->SetText("Logout");
    logout_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    logout_button->RegisterOnClick(logout_listener);


    GuiFrame* character_frame_1 = CreateCharacterFrame(font);
    GuiFrame* character_frame_2 = CreateCharacterFrame(font);

    character_frame_1->SetPosition(Vector2(260, 20 + 190*0));
    character_frame_2->SetPosition(Vector2(260, 20 + 190*1));

    static_cast<GuiButton*>(character_frame_1->GetGuiById("login_button"))->RegisterOnClick(login_listener_1);
    static_cast<GuiButton*>(character_frame_2->GetGuiById("login_button"))->RegisterOnClick(login_listener_2);



    base_frame->AddChild(create_char_button);
    base_frame->AddChild(logout_button);
    base_frame->AddChild(character_frame_1);
    base_frame->AddChild(character_frame_2);

    GuiScreen* screen = new GuiScreen(base_frame);
    screen->RegisterListener(logout_listener);
    screen->RegisterListener(login_listener_1);
    screen->RegisterListener(login_listener_2);

    screen->SetGuiId("character_frame_1", character_frame_1);
    screen->SetGuiId("character_frame_2", character_frame_2);

    return screen;
}
