#include "screenmaker.hpp"

#include "gamestatecharacterview.hpp"
#include "bitmapservice.hpp"

static const int BASE_WIDTH = 32;
static const int UPPER_ALIGN = 480*0.23;
static const int LOWER_ALIGN = 480 * 0.7;
static const int LEFT_ALIGN = 640/5;
static const int BUTTON_ALIGN = 640*0.57;
namespace CharacterCreationListeners
{
    class DirectionLeftEvent : public GameEventBase
    {
    public:
        DirectionLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //change direction clockwise
            Character * display_toon =this->game->GetCurrentCharacter();
            display_toon->SetDirection( static_cast<Actor::Direction>((display_toon->GetDirection()-1)%4));
            display_toon->Update();
        }
    };
    class DirectionLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        DirectionLeftListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new DirectionLeftEvent(this->game));
        }
    };

    class DirectionRightEvent: public GameEventBase
    {
    public:
        DirectionRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            Character * display_toon =this->game->GetCurrentCharacter();
            display_toon->SetDirection( static_cast<Actor::Direction>((display_toon->GetDirection()+1)%4));
            display_toon->Update();
        }
    };
    class DirectionRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        DirectionRightListener(Game * game): game(game) {}
        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new DirectionRightEvent(this->game));
        }
    };

    class CreateEvent: public GameEventBase
    {
    public:
        CreateEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class CreatetListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        CreatetListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new CreateEvent(this->game));
        }
    };

    class CancelEvent: public GameEventBase
    {
    public:
        CancelEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            this->game->PopScreen();
            this->game->ChangeState(new GameStateCharacterView(this->game));
            //to do
        }
    };
    class CancelListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        CancelListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new CancelEvent(this->game));
        }
    };

    class FemaleEvent: public GameEventBase
    {
    public:
        FemaleEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class FemaleListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        FemaleListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new FemaleEvent(this->game));
        }
    };

    class MaleEvent: public GameEventBase
    {
    public:
        MaleEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class MaleListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        MaleListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new MaleEvent(this->game));
        }
    };

    class SkinLeftEvent: public GameEventBase
    {
    public:
        SkinLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class SkinLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        SkinLeftListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new SkinLeftEvent(this->game));
        }
    };

    class SkinRightEvent: public GameEventBase
    {
    public:
        SkinRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class SkinRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        SkinRightListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new SkinRightEvent(this->game));
        }
    };

    class HairLeftEvent: public GameEventBase
    {
    public:
        HairLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class HairLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        HairLeftListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new HairLeftEvent(this->game));
        }
    };

    class HairRightEvent: public GameEventBase
    {
    public:
        HairRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class HairRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        HairRightListener(Game * game): game(game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new HairRightEvent(this->game));
        }
    };

    class ColorEvent: public GameEventBase
    {
    protected:
        std::string color;
    public:
        ColorEvent(Game * game, std::string color): GameEventBase(game),color(color) {}

        virtual void HandleEvent()
        {
            //to do
        }
    };
    class ColorListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;
        std::string color;

    public:
        ColorListener(Game * game, std::string color): game(game), color(color) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            this->game->RegisterEventToQueue(new ColorEvent(this->game, color));
        }
    };
}

GuiScreen * SreenMakerCharacterCreation::MakeScreen()
{
    this->game->LoginAsCharacter(new Character());
    this->game->GetCurrentCharacter()->SetDirection(Character::DIR_RIGHT);
    ALLEGRO_FONT * button_font = nullptr;

    GuiScreen * screen = nullptr;

//    CharacterCreationListeners::DirectionLeftListener * mouse_enter_listener = nullptr;
//    CharacterCreationListeners::DirectionRightListener * mouse_leave_listener = nullptr;
    CharacterCreationListeners::DirectionLeftListener * change_direction_left = nullptr;
    CharacterCreationListeners::DirectionRightListener * change_direction_right = nullptr;
    CharacterCreationListeners::CreatetListener * create_listener = nullptr;
    CharacterCreationListeners::CancelListener * cancel_listener = nullptr;
    CharacterCreationListeners::FemaleListener * female_listener = nullptr;
    CharacterCreationListeners::MaleListener * male_listener = nullptr;
    CharacterCreationListeners::SkinLeftListener * skin_left_listener = nullptr;
    CharacterCreationListeners::SkinRightListener * skin_right_listener = nullptr;
    CharacterCreationListeners::HairLeftListener * hair_left_listener = nullptr;
    CharacterCreationListeners::HairRightListener * hair_right_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_brown_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_black_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_white_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_purple_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_light_blue_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_red_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_green_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_dark_blue_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_yellow_listener = nullptr;
    CharacterCreationListeners::ColorListener * color_pink_listener = nullptr;

    GuiFrame * parent_frame = nullptr;
    GuiFrame * character_background_frame = nullptr;
    GuiFrame * hair_color_frame = nullptr;

    GuiImageLabel * background = nullptr;

    GuiTextLabel * user_name_label = nullptr;
    GuiTextLabel * gender_label = nullptr;
    GuiTextLabel * skin_label = nullptr;
    GuiTextLabel * skin_name_label = nullptr;
    GuiTextLabel * hair_label = nullptr;
    GuiTextLabel * hair_name_label = nullptr;
    GuiTextLabel * hair_color_label = nullptr;

    GuiTextBox * user_name_text = nullptr;

    GuiTextButton * create_button = nullptr;
    GuiTextButton * cancel_button = nullptr;
    GuiTextButton * change_direction_left_button = nullptr;
    GuiTextButton * change_direction_right_button = nullptr;
    GuiTextButton * female_button = nullptr;
    GuiTextButton * male_button = nullptr;
    GuiTextButton * skin_left_button = nullptr;
    GuiTextButton * skin_right_button = nullptr;
    GuiTextButton * hair_left_button = nullptr;
    GuiTextButton * hair_right_button = nullptr;
    GuiButton * color_brown_button = nullptr;
    GuiButton * color_black_button = nullptr;
    GuiButton * color_white_button = nullptr;
    GuiButton * color_purple_button = nullptr;
    GuiButton * color_light_blue_button = nullptr;
    GuiButton * color_red_button = nullptr;
    GuiButton * color_green_button = nullptr;
    GuiButton * color_dark_blue_button = nullptr;
    GuiButton * color_yellow_button = nullptr;
    GuiButton * color_pink_button = nullptr;

    //font
    button_font = FontService::Instance()->GetFont("title_button");

    //listeners
//    mouse_enter_listener = nullptr;
//    mouse_leave_listener = nullptr;
    change_direction_left = new CharacterCreationListeners::DirectionLeftListener(this->game);
    change_direction_right = new CharacterCreationListeners::DirectionRightListener(this->game);;
    create_listener = new CharacterCreationListeners::CreatetListener(this->game);
    cancel_listener = new CharacterCreationListeners::CancelListener(this->game);;
    female_listener = new CharacterCreationListeners::FemaleListener(this->game);;
    male_listener = new CharacterCreationListeners::MaleListener(this->game);;
    skin_left_listener = new CharacterCreationListeners::SkinLeftListener(this->game);;
    skin_right_listener = new CharacterCreationListeners::SkinRightListener(this->game);;
    hair_left_listener = new CharacterCreationListeners::HairLeftListener(this->game);;
    hair_right_listener = new CharacterCreationListeners::HairRightListener(this->game);;
    color_brown_listener = new CharacterCreationListeners::ColorListener(this->game, "brown");
    color_black_listener = new CharacterCreationListeners::ColorListener(this->game, "black");
    color_white_listener = new CharacterCreationListeners::ColorListener(this->game, "white");
    color_purple_listener = new CharacterCreationListeners::ColorListener(this->game, "purple");
    color_light_blue_listener = new CharacterCreationListeners::ColorListener(this->game, "light blue");
    color_red_listener = new CharacterCreationListeners::ColorListener(this->game, "red");
    color_green_listener = new CharacterCreationListeners::ColorListener(this->game, "green");
    color_dark_blue_listener = new CharacterCreationListeners::ColorListener(this->game, "dark blue");
    color_yellow_listener = new CharacterCreationListeners::ColorListener(this->game, "yellow");
    color_pink_listener = new CharacterCreationListeners::ColorListener(this->game, "pink");

    //frame
    parent_frame = new GuiFrame(Vector2(640 ,480 ), Vector2(0, 0));
    character_background_frame = new GuiFrame(Vector2(BASE_WIDTH*1.68*1.68, BASE_WIDTH *4), Vector2(LEFT_ALIGN, UPPER_ALIGN));
    hair_color_frame = new GuiFrame(Vector2(640 * (0.35) , BASE_WIDTH*4), Vector2(LEFT_ALIGN +BASE_WIDTH*4, UPPER_ALIGN+25*4));
    std::cout << 25 << std::endl;
    //labels
    background = new GuiImageLabel(parent_frame->GetSize());
    background->SetImage(BitmapService::Instance()->GetBitmap("background_1"));

    user_name_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(LEFT_ALIGN +BASE_WIDTH*4, UPPER_ALIGN));
    user_name_label->SetText("Username:");
    user_name_label->SetTextFont(button_font);
    user_name_label->SetTextColor(Color3(250,250,250));
    user_name_label->SetBackgroundAlpha(0);

    gender_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(LEFT_ALIGN +BASE_WIDTH*4, UPPER_ALIGN+25));
    gender_label->SetText("Gender:");
    gender_label->SetTextFont(button_font);
    gender_label->SetTextColor(Color3(250,250,250));
    gender_label->SetBackgroundAlpha(0);

    skin_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(LEFT_ALIGN +BASE_WIDTH*4, UPPER_ALIGN+25*2));
    skin_label->SetText("Skin:");
    skin_label->SetTextFont(button_font);
    skin_label->SetTextColor(Color3(250,250,250));
    skin_label->SetBackgroundAlpha(0);

    skin_name_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(BUTTON_ALIGN+25, UPPER_ALIGN+25*2));
    skin_name_label->SetText("Skin type");
    skin_name_label->SetTextFont(button_font);
    skin_name_label->SetTextColor(Color3(250,250,250));
    skin_name_label->SetBackgroundAlpha(66);
    skin_name_label->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    hair_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(LEFT_ALIGN +BASE_WIDTH*4, UPPER_ALIGN+25*3));
    hair_label->SetText("Hair:");
    hair_label->SetTextFont(button_font);
    hair_label->SetTextColor(Color3(250,250,250));
    hair_label->SetBackgroundAlpha(0);

    hair_name_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(BUTTON_ALIGN+25, UPPER_ALIGN+25*3));
    hair_name_label->SetText("Hair Type");
    hair_name_label->SetTextFont(button_font);
    hair_name_label->SetTextColor(Color3(250,250,250));
    hair_name_label->SetBackgroundAlpha(66);
    hair_name_label->SetTextAlign(GuiTextButton::ALIGN_CENTER);

    hair_color_label = new GuiTextLabel(Vector2(640*0.2, 25), Vector2(0, 0));
    hair_color_label->SetText("Hair Color:");
    hair_color_label->SetTextFont(button_font);
    hair_color_label->SetTextColor(Color3(250,250,250));
    hair_color_label->SetBackgroundAlpha(0);

    //buttons
    create_button = new GuiTextButton(Vector2(BASE_WIDTH*1.68*1.68, 25), Vector2(LEFT_ALIGN, (UPPER_ALIGN + BASE_WIDTH *5)));
    cancel_button = new GuiTextButton(Vector2(BASE_WIDTH*1.68*1.68, 25), Vector2(LEFT_ALIGN, (UPPER_ALIGN + BASE_WIDTH *5)+25*1.6));
    change_direction_left_button = new GuiTextButton(Vector2(25, 25), Vector2(0, 0 + BASE_WIDTH *4 - 25));
    change_direction_right_button = new GuiTextButton(Vector2(25, 25), Vector2(0+BASE_WIDTH *1.68*1.68 - 25, 0 + BASE_WIDTH *4 - 25));
    female_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN, UPPER_ALIGN+25));
    male_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN+25*6, UPPER_ALIGN+25));
    skin_left_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN, UPPER_ALIGN+25*2));
    skin_right_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN+25*6, UPPER_ALIGN+25*2));
    hair_left_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN, UPPER_ALIGN+25*3));
    hair_right_button = new GuiTextButton(Vector2(25, 25), Vector2(BUTTON_ALIGN+25*6, UPPER_ALIGN+25*3));
    color_brown_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618, 25 * 1.6));
    color_black_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25* 1.6, 25 * 1.6));
    color_white_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*2* 1.6, 25 * 1.6));
    color_purple_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*3* 1.6, 25 * 1.6));
    color_light_blue_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*4* 1.6, 25 * 1.6));
    color_red_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 , 25 *2 * 1.6));
    color_green_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25* 1.6, 25*2 * 1.6));
    color_dark_blue_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*2* 1.6, 25*2 * 1.6));
    color_yellow_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*3* 1.6, 25*2 * 1.6));
    color_pink_button = new GuiTextButton(Vector2(25, 25), Vector2(25*.618 +25*4* 1.6,25*2 * 1.6));

    //text boxes
    user_name_text = new GuiTextBox(Vector2(25*7, 25), Vector2(BUTTON_ALIGN, UPPER_ALIGN));



    //setup buttons
    create_button->SetText("Create");
    create_button->SetTextColor(Color3(255,255,255));
    create_button->SetTextFont(button_font);
    create_button->SetBackgroundColor(Color3(55,55,55));
    create_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    create_button->RegisterOnClick(create_listener);

    cancel_button->SetText("Cancel");
    cancel_button->SetTextColor(Color3(255,255,255));
    cancel_button->SetTextFont(button_font);
    cancel_button->SetBackgroundColor(Color3(55,55,55));
    cancel_button->SetTextAlign(GuiTextButton::ALIGN_CENTER);
    cancel_button->RegisterOnClick(cancel_listener);

    change_direction_left_button->SetBackgroundColor(Color3(0,0,255*0.618));
    change_direction_left_button->RegisterOnClick(change_direction_left);
    //change_direction_left_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_2"));

    change_direction_right_button->SetBackgroundColor(Color3(0,0,255*0.618));
    change_direction_right_button->RegisterOnClick(change_direction_right);
    //change_direction_right_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_3"));

    female_button->SetBackgroundColor(Color3(0,152,255));
    female_button->RegisterOnClick(female_listener);
    //female_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_0"));

    male_button->SetBackgroundColor(Color3(0,152,255));
    male_button->RegisterOnClick(male_listener);
    //male_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_1"));

    skin_left_button->SetBackgroundColor(Color3(0,255,255));
    skin_left_button->RegisterOnClick(skin_left_listener);
    //skin_left_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_2"));

    skin_right_button->SetBackgroundColor(Color3(0,255,255));
    skin_right_button->RegisterOnClick(skin_right_listener);
    //skin_right_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_3"));

    hair_left_button->SetBackgroundColor(Color3(155,255,255));
    hair_left_button->RegisterOnClick(hair_left_listener);
    //hair_left_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_2"));

    hair_right_button->SetBackgroundColor(Color3(155,255,255));
    hair_right_button->RegisterOnClick(hair_right_listener);
    //hair_right_button->SetImage(BitmapService::Instance()->GetBitmap("guielement_3"));

    color_brown_button->SetBackgroundColor(Color3(74,0,0));
    color_brown_button->RegisterOnClick(color_brown_listener);

    color_black_button->SetBackgroundColor(Color3(82,82,82));
    color_black_button->RegisterOnClick(color_black_listener);

    color_white_button->SetBackgroundColor(Color3(214,214,214));;
    color_white_button->RegisterOnClick(color_white_listener);

    color_purple_button->SetBackgroundColor(Color3(149, 65,165));;
    color_purple_button->RegisterOnClick(color_purple_listener);

    color_light_blue_button->SetBackgroundColor(Color3(115,156,198));;
    color_light_blue_button->RegisterOnClick(color_light_blue_listener);

    color_red_button->SetBackgroundColor(Color3(239,33,8));;
    color_red_button->RegisterOnClick(color_red_listener);

    color_green_button->SetBackgroundColor(Color3(90,148,33));;
    color_green_button->RegisterOnClick(color_green_listener);

    color_dark_blue_button->SetBackgroundColor(Color3(49,74,215));;
    color_dark_blue_button->RegisterOnClick(color_dark_blue_listener);

    color_yellow_button->SetBackgroundColor(Color3(255,189,74));;
    color_yellow_button->RegisterOnClick(color_yellow_listener);

    color_pink_button->SetBackgroundColor(Color3(231,123,173));;
    color_pink_button->RegisterOnClick(color_pink_listener);

    //setup text boxes
    user_name_text->SetTextFont(button_font);
    user_name_text->SetTextColor(Color3(50,50,50));
    user_name_text->SetText("bob");
    user_name_text->SetBackgroundAlpha(30);
    user_name_text->SetBackgroundColor(Color3(155,155,155));

    //setup frames
    parent_frame->SetBackgroundColor(Color3(255,255,255));
    character_background_frame->SetBackgroundColor(Color3(55,55,55));
    character_background_frame->SetBackgroundAlpha(66);
    hair_color_frame->SetBackgroundColor(Color3(55,55,55));

    character_background_frame->AddChild(change_direction_left_button);
    character_background_frame->AddChild(change_direction_right_button);

    hair_color_frame->AddChild(hair_color_label);
    hair_color_frame->AddChild(color_brown_button);
    hair_color_frame->AddChild(color_black_button);
    hair_color_frame->AddChild(color_white_button);
    hair_color_frame->AddChild(color_purple_button);
    hair_color_frame->AddChild(color_light_blue_button);
    hair_color_frame->AddChild(color_red_button);
    hair_color_frame->AddChild(color_green_button);
    hair_color_frame->AddChild(color_dark_blue_button);
    hair_color_frame->AddChild(color_yellow_button);
    hair_color_frame->AddChild(color_pink_button);

    parent_frame->AddChild(background);
    parent_frame->AddChild(character_background_frame);
    parent_frame->AddChild(hair_color_frame);
    parent_frame->AddChild(user_name_label);
    parent_frame->AddChild(gender_label);
    parent_frame->AddChild(skin_label);
    parent_frame->AddChild(skin_name_label);
    parent_frame->AddChild(hair_label);
    parent_frame->AddChild(hair_name_label);
//    parent_frame->AddChild(change_direction_left_button);
//    parent_frame->AddChild(change_direction_right_button);
    parent_frame->AddChild(female_button);
    parent_frame->AddChild(male_button);
    parent_frame->AddChild(skin_left_button);
    parent_frame->AddChild(skin_right_button);
    parent_frame->AddChild(hair_left_button);
    parent_frame->AddChild(hair_right_button);
    parent_frame->AddChild(user_name_text);
    parent_frame->AddChild(cancel_button);
    parent_frame->AddChild(create_button);

    parent_frame->SetGuiId("char_frame",character_background_frame);

    //setup screen
    screen = new GuiScreen(parent_frame);
    screen->RegisterListener(change_direction_left);
    screen->RegisterListener(change_direction_right);
    screen->RegisterListener(create_listener);
    screen->RegisterListener(cancel_listener);
    screen->RegisterListener(female_listener);
    screen->RegisterListener(male_listener);
    screen->RegisterListener(skin_left_listener);
    screen->RegisterListener(skin_right_listener);
    screen->RegisterListener(hair_left_listener);
    screen->RegisterListener(hair_right_listener);
    screen->RegisterListener(color_brown_listener);
    screen->RegisterListener(color_black_listener);
    screen->RegisterListener(color_white_listener);
    screen->RegisterListener(color_purple_listener);
    screen->RegisterListener(color_light_blue_listener);
    screen->RegisterListener(color_red_listener);
    screen->RegisterListener(color_green_listener);
    screen->RegisterListener(color_dark_blue_listener);
    screen->RegisterListener(color_yellow_listener);
    screen->RegisterListener(color_pink_listener);

    screen->SetGuiId("parent_frame", parent_frame);

    return screen;
}
