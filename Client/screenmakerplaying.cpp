#include "screenmaker.hpp"
#include "gamestatecharacterview.hpp"

namespace PlayingScreen
{
    class LogoutEvent: public GameEventBase
    {
    public:
        LogoutEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            PacketCharacterLogout* packet = new PacketCharacterLogout();
            this->game->SendPacket(packet);

            ScreenMakerCharacterView maker(this->game);
            this->game->PushScreen(maker.MakeScreen());

            this->game->SetCurrentCharacter(nullptr);
            this->game->ChangeState(new GameStateCharacterView(this->game));
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
}
GuiFrame* CreateBarFrame(Color3 main_bar_color, std::string stat)
{
    Color3 bar_base_color = Color3(180, 180, 180);
    Vector2 bar_base_rounding = Vector2(4, 4);
    char bar_base_alpha = 160;

    GuiFrame* bar_frame = new GuiFrame(Vector2(120, 40), Vector2(0, 0));
    bar_frame->SetBackgroundAlpha(0);

    GuiTextLabel* bar_text = new GuiTextLabel(Vector2(116, 14), Vector2(4, 0));
    bar_text->SetBackgroundAlpha(0);
    bar_text->SetTextFont(FontService::Instance()->GetFont("stat_bar"));
    bar_text->SetText(stat.c_str());
    bar_text->SetTextColor(Color3(255, 255, 255));

    GuiFrame* bar_base = new GuiFrame(Vector2(112, 26), Vector2(4, 16));
    bar_base->SetBackgroundColor(bar_base_color);
    bar_base->SetRounding(bar_base_rounding);
    bar_base->SetBackgroundAlpha(bar_base_alpha);

    GuiFrame* bar_main = new GuiFrame(Vector2(112, 26), Vector2(4, 16));
    bar_main->SetRounding(bar_base_rounding);
    bar_main->SetBackgroundColor(main_bar_color);

    bar_frame->AddChild(bar_text);
    bar_frame->AddChild(bar_base);
    bar_frame->AddChild(bar_main);

    bar_frame->SetGuiId("bar_text", bar_text);
    bar_frame->SetGuiId("bar_main", bar_main);

    return bar_frame;
}

GuiFrame * CreateMenuFrame ()
{
    GuiFrame * parent = new GuiFrame(Vector2(640/6, 480/4), Vector2(5*640/6, 3*480/4));
    parent->SetBackgroundColor(Color3(231, 199, 150));

    GuiTextButton * logout = new GuiTextButton(Vector2(640/6-8, 32), Vector2(4, 120-36));
    logout->SetTextFont(FontService::Instance()->GetFont("title_button"));
    logout->SetText("Logout");
    logout->SetBackgroundColor(Color3(200, 170, 120));
    logout->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    parent->AddChild(logout);
    parent->SetGuiId("logout", logout);

    return parent;
}

GuiFrame * CreateeExperienceBar()
{

}

GuiScreen* ScreenMakerPlaying::MakeScreen()
{
    PlayingScreen::LogoutListener * logout_listener = new PlayingScreen::LogoutListener(this->game);
    GuiBase * cursor;
    GuiFrame* base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundAlpha(0);

    GuiFrame* bar_frame_base = new GuiFrame(Vector2(244, 44), Vector2(120, 0));
    bar_frame_base->SetBackgroundAlpha(120);
    GuiFrame* menu_frame = CreateMenuFrame();

    GuiFrame* bar_frame_health = CreateBarFrame(Color3(186, 29, 34), "Health");
    GuiFrame* bar_frame_mana = CreateBarFrame(Color3(34, 29, 186), "Magic");
    bar_frame_mana->SetPosition(Vector2(124,0));

    bar_frame_base->AddChild(bar_frame_health);
    bar_frame_base->AddChild(bar_frame_mana);

    base_frame->AddChild(bar_frame_base);
    base_frame->AddChild(menu_frame);

    cursor = menu_frame->GetGuiById("logout");
    static_cast<GuiTextButton *>(cursor)->RegisterOnClick(logout_listener);

    cursor = bar_frame_health->GetGuiById("bar_main");
    GuiScreen* screen = new GuiScreen(base_frame);
    screen->SetGuiId("health_bar", cursor);
    cursor = bar_frame_mana->GetGuiById("bar_main");
    screen->SetGuiId("magic_bar", cursor);
    screen->RegisterListener(logout_listener);

    return screen;
}
