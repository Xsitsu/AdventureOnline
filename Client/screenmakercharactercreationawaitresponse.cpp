#include "screenmaker.hpp"
#include "gamestatecharactercreation.hpp"

namespace CharacterCreationAwaitResponse
{
    GuiTextButton* CreateButton(int offset, std::string button_text, ALLEGRO_FONT* text_font)
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

    GuiTextLabel* CreateLabel(int offset, std::string button_text, ALLEGRO_FONT* text_font)
    {
        Color3 button_background = Color3(0, 0, 0);
        char button_background_alpha = 180;
        Vector2 button_size = Vector2(200, 26);
        Vector2 button_start_pos = Vector2(640*.5 - button_size.x, 0*.5 + button_size.y) / 2;
        Vector2 button_offset = Vector2(0, 34);

        GuiTextLabel* button = new GuiTextLabel(button_size, button_start_pos + (button_offset * offset));
        button->SetBackgroundColor(button_background);
        button->SetBackgroundAlpha(button_background_alpha);
        button->SetText(button_text);
        button->SetTextColor(Color3(255, 255, 255));
        button->SetTextAlign(GuiTextLabel::ALIGN_CENTER);
        button->SetTextFont(text_font);

        return button;
    }

    class ContinueEvent : public GameEventBase
    {
    public:
        ContinueEvent(Game* game) : GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();

            this->game->ChangeState(new GameStateCharacterCreation(this->game));
        }
    };

    class ContinueListener : public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game* game;

    public:
        ContinueListener(Game* game) : game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new CharacterCreationAwaitResponse::ContinueEvent(this->game));
        }
    };
}

GuiScreen * SreenMakerCharacterCreationAwaitResponse::MakeScreen()
{
    ALLEGRO_FONT * button_font = FontService::Instance()->GetFont("title_button");
    CharacterCreationAwaitResponse::ContinueListener * done_listener = new CharacterCreationAwaitResponse::ContinueListener(this->game);

    GuiFrame * waitFrame = new GuiFrame(Vector2(640 * 0.50,480 * 0.50), Vector2(640*0.25, 480*0.25));

    GuiTextLabel * information = CharacterCreationAwaitResponse::CreateLabel(3, "Waiting for response from server", button_font);
    GuiTextButton * accept_button = CharacterCreationAwaitResponse::CreateButton(5, "Continue", button_font);

    accept_button->RegisterOnClick(done_listener);
    information->SetBackgroundAlpha(0);

    waitFrame->SetBackgroundColor(Color3(0, 50, 0));
    waitFrame->AddChild(information);
    waitFrame->AddChild(accept_button);

    GuiScreen* screen = new GuiScreen(waitFrame);

    screen->RegisterListener(done_listener);

    screen->SetGuiId("Confirmation", information);
    screen->SetGuiId("Continue", accept_button);

    return screen;
}
