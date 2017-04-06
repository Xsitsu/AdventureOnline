#include "screenmaker.hpp"

#include "gamestatecharacterview.hpp"

namespace CharacterCreationListeners
{
    class DirectionLeftEvent :public GameEventBase
    {
    public:
        DirectionLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            //change direction clockwise
            std::cout << "clockwise" << std::endl;
        }
    };
    class DirectionLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        DirectionLeftListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new DirectionLeftEvent(game));
        }
    };

    class DirectionRightEvent: public GameEventBase
    {
    public:
        DirectionRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "counter clockwise" << std::endl;
            //change direction counterclockwise
        }
    };
    class DirectionRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        DirectionRightListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new DirectionRightEvent(game));
        }
    };

    class CreateEvent: public GameEventBase
    {
    public:
        CreateEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "create" << std::endl;
            //to do
        }
    };
    class CreatetListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        CreatetListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new CreateEvent(game));
        }
    };

    class CancelEvent: public GameEventBase
    {
    public:
        CancelEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "cancel" << std::endl;
            game->PopScreen();
            game->ChangeState(new GameStateCharacterView(game));
            //to do
        }
    };
    class CancelListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        CancelListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new CancelEvent(game));
        }
    };

    class FemaleEvent: public GameEventBase
    {
    public:
        FemaleEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "female" << std::endl;
            //to do
        }
    };
    class FemaleListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        FemaleListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new FemaleEvent(game));
        }
    };

    class MaleEvent: public GameEventBase
    {
    public:
        MaleEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "male" << std::endl;
            //to do
        }
    };
    class MaleListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        MaleListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new MaleEvent(game));
        }
    };

    class SkinLeftEvent: public GameEventBase
    {
    public:
        SkinLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "skin left change" << std::endl;
            //to do
        }
    };
    class SkinLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        SkinLeftListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new SkinLeftEvent(game));
        }
    };

    class SkinRightEvent: public GameEventBase
    {
    public:
        SkinRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "skin right event" << std::endl;
            //to do
        }
    };
    class SkinRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        SkinRightListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new SkinRightEvent(game));
        }
    };

    class HairLeftEvent: public GameEventBase
    {
    public:
        HairLeftEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "hair left event" << std::endl;
            //to do
        }
    };
    class HairLeftListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        HairLeftListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new HairLeftEvent(game));
        }
    };

    class HairRightEvent: public GameEventBase
    {
    public:
        HairRightEvent(Game * game): GameEventBase(game) {}

        virtual void HandleEvent()
        {
            std::cout << "hair right event" << std::endl;
            //to do
        }
    };
    class HairRightListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;

    public:
        HairRightListener(Game * game) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new HairRightEvent(game));
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
            std::cout << "color event: " << color <<  std::endl;
            //to do
        }
    };
    class ColorListener: public ListenerBase<GuiButtonArgs*>
    {
    protected:
        Game * game;
        std::string color;

    public:
        ColorListener(Game * game, std::string color) {}

        virtual void Notify(GuiButtonArgs*& args) const
        {
            game->RegisterEventToQueue(new ColorEvent(game, color));
        }
    };
}

GuiScreen * SreenMakerCharacterCreation::MakeScreen()
{
    game->LoginAsCharacter(new Character());
    game->GetCurrentCharacter()->SetDirection(Character::DIR_RIGHT);
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
    GuiButton * change_direction_left_button = nullptr;
    GuiButton * change_direction_right_button = nullptr;
    GuiButton * female_button = nullptr;
    GuiButton * male_button = nullptr;
    GuiButton * skin_left_button = nullptr;
    GuiButton * skin_right_button = nullptr;
    GuiButton * hair_left_button = nullptr;
    GuiButton * hair_right_button = nullptr;
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
    change_direction_left = new CharacterCreationListeners::DirectionLeftListener(game);
    change_direction_right = new CharacterCreationListeners::DirectionRightListener(game);;
    create_listener = new CharacterCreationListeners::CreatetListener(game);
    cancel_listener = new CharacterCreationListeners::CancelListener(game);;
    female_listener = new CharacterCreationListeners::FemaleListener(game);;
    male_listener = new CharacterCreationListeners::MaleListener(game);;
    skin_left_listener = new CharacterCreationListeners::SkinLeftListener(game);;
    skin_right_listener = new CharacterCreationListeners::SkinRightListener(game);;
    hair_left_listener = new CharacterCreationListeners::HairLeftListener(game);;
    hair_right_listener = new CharacterCreationListeners::HairRightListener(game);;
    color_brown_listener = new CharacterCreationListeners::ColorListener(game, "brown");
    color_black_listener = new CharacterCreationListeners::ColorListener(game, "black");
    color_white_listener = new CharacterCreationListeners::ColorListener(game, "white");
    color_purple_listener = new CharacterCreationListeners::ColorListener(game, "purple");
    color_light_blue_listener = new CharacterCreationListeners::ColorListener(game, "light blue");
    color_red_listener = new CharacterCreationListeners::ColorListener(game, "red");
    color_green_listener = new CharacterCreationListeners::ColorListener(game, "green");
    color_dark_blue_listener = new CharacterCreationListeners::ColorListener(game, "dark blue");
    color_yellow_listener = new CharacterCreationListeners::ColorListener(game, "yellow");
    color_pink_listener = new CharacterCreationListeners::ColorListener(game, "pink");

    //frame
    parent_frame = new GuiFrame(Vector2(640 ,480 ), Vector2(0, 0));
    character_background_frame = new GuiFrame(Vector2(640 * 0.35,480 * 0.6), Vector2(640*0.10, 480*0.10));
    hair_color_frame = new GuiFrame(Vector2(640 * (0.35) ,480 * 0.35), Vector2(640*0.45 +10, 480*0.60));

    //labels
    user_name_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.45 +10, 6));
    user_name_label->SetText("Username:");
    user_name_label->SetTextFont(button_font);
    user_name_label->SetTextColor(Color3(100,100,100));
    gender_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.45 +10, 6+button_font->height*1.6));
    gender_label->SetText("Gender:");
    gender_label->SetTextFont(button_font);
    gender_label->SetTextColor(Color3(100,100,100));
    skin_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.45 +10, 6+button_font->height*2*1.6));
    skin_label->SetText("Skin:");
    skin_label->SetTextFont(button_font);
    skin_label->SetTextColor(Color3(100,100,100));
    skin_name_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.65 +10+button_font->height, 6+button_font->height*2*1.6));
    skin_name_label->SetText("Skin type:");
    skin_name_label->SetTextFont(button_font);
    skin_name_label->SetTextColor(Color3(100,100,100));
    hair_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.45 +10, 6+button_font->height*3*1.6));
    hair_label->SetText("Hair:");
    hair_label->SetTextFont(button_font);
    hair_label->SetTextColor(Color3(100,100,100));
    hair_name_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(640*0.65 +10+button_font->height, 6+button_font->height*3*1.6));
    hair_name_label->SetText("Hair Type:");
    hair_name_label->SetTextFont(button_font);
    hair_name_label->SetTextColor(Color3(100,100,100));
    hair_color_label = new GuiTextLabel(Vector2(640*0.2, button_font->height), Vector2(0, 0));
    hair_color_label->SetText("Hair Color:");
    hair_color_label->SetTextFont(button_font);
    hair_color_label->SetTextColor(Color3(100,100,100));

    //buttons
    create_button = new GuiTextButton(Vector2(640*.175, button_font->height), Vector2(640*0.10, 480*0.7+10));
    cancel_button = new GuiTextButton(Vector2(640*.175, button_font->height), Vector2(640*0.275 +10, 480*0.7+10));
    change_direction_left_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.1, 480*0.7-button_font->height));
    change_direction_right_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.45-button_font->height, 480*0.7-button_font->height));
    female_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.65+10, 6+button_font->height*1.6));
    male_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.85+10, 6+button_font->height*1.6));
    skin_left_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.65+10, 6+button_font->height*2*1.6));
    skin_right_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.85+10, 6+button_font->height*2*1.6));
    hair_left_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.65+10, 6+button_font->height*3*1.6));
    hair_right_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(640*0.85+10, 6+button_font->height*3*1.6));
    color_brown_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0, button_font->height * 1.6));
    color_black_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height* 1.6, button_font->height * 1.6));
    color_white_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*2* 1.6, button_font->height * 1.6));
    color_purple_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*3* 1.6, button_font->height * 1.6));
    color_light_blue_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*4* 1.6, button_font->height * 1.6));
    color_red_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 , button_font->height *2 * 1.6));
    color_green_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height* 1.6, button_font->height*2 * 1.6));
    color_dark_blue_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*2* 1.6, button_font->height*2 * 1.6));
    color_yellow_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*3* 1.6, button_font->height*2 * 1.6));
    color_pink_button = new GuiImageButton(Vector2(button_font->height, button_font->height), Vector2(0 +button_font->height*4* 1.6,button_font->height*2 * 1.6));

    //text boxes
    user_name_text = new GuiTextBox(Vector2(640*0.2, button_font->height), Vector2(640*0.65 +10, 6));



    //setup buttons
    create_button->SetText("Create");
    create_button->RegisterOnClick(create_listener);
    create_button->SetTextColor(Color3(100,100,100));
    create_button->SetTextFont(button_font);
    cancel_button->SetText("Cancel");
    cancel_button->RegisterOnClick(cancel_listener);
    cancel_button->SetTextColor(Color3(100,100,100));
    cancel_button->SetTextFont(button_font);
    change_direction_left_button->SetBackgroundColor(Color3(0,0,255));
    change_direction_left_button->RegisterOnClick(change_direction_left);
    change_direction_right_button->SetBackgroundColor(Color3(0,0,255));
    change_direction_right_button->RegisterOnClick(change_direction_right);
    female_button->SetBackgroundColor(Color3(0,152,255));
    female_button->RegisterOnClick(female_listener);
    male_button->SetBackgroundColor(Color3(0,152,255));
    male_button->RegisterOnClick(male_listener);
    skin_left_button->SetBackgroundColor(Color3(0,255,255));
    skin_left_button->RegisterOnClick(skin_left_listener);
    skin_right_button->SetBackgroundColor(Color3(0,255,255));
    skin_right_button->RegisterOnClick(skin_right_listener);
    hair_left_button->SetBackgroundColor(Color3(155,255,255));
    hair_left_button->RegisterOnClick(hair_left_listener);
    hair_right_button->SetBackgroundColor(Color3(155,255,255));
    hair_right_button->RegisterOnClick(hair_right_listener);
    color_brown_button->SetBackgroundColor(Color3(185,148,120));
    color_brown_button->RegisterOnClick(color_brown_listener);
    color_black_button->SetBackgroundColor(Color3(0,0,0));
    color_black_button->RegisterOnClick(color_black_listener);
    color_white_button->SetBackgroundColor(Color3(255,255,255));;
    color_white_button->RegisterOnClick(color_white_listener);
    color_purple_button->SetBackgroundColor(Color3(128,0,128));;
    color_purple_button->RegisterOnClick(color_purple_listener);
    color_light_blue_button->SetBackgroundColor(Color3(135,206,250));;
    color_light_blue_button->RegisterOnClick(color_light_blue_listener);
    color_red_button->SetBackgroundColor(Color3(255,0,0));;
    color_red_button->RegisterOnClick(color_red_listener);
    color_green_button->SetBackgroundColor(Color3(0,255,0));;
    color_green_button->RegisterOnClick(color_green_listener);
    color_dark_blue_button->SetBackgroundColor(Color3(0,0,255));;
    color_dark_blue_button->RegisterOnClick(color_dark_blue_listener);
    color_yellow_button->SetBackgroundColor(Color3(255,255,0));;
    color_yellow_button->RegisterOnClick(color_yellow_listener);
    color_pink_button->SetBackgroundColor(Color3(255,182,193));;
    color_pink_button->RegisterOnClick(color_pink_listener);

    //setup text boxes
    user_name_text->SetTextFont(button_font);
    user_name_text->SetTextColor(Color3(100,100,100));
    user_name_text->SetText("myname");
    user_name_text->SetBackgroundAlpha(80);

    //setup frames
    character_background_frame->AddChild(change_direction_left_button);
    character_background_frame->AddChild(change_direction_right_button);
    character_background_frame->SetBackgroundColor(Color3(55,55,55));

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
    hair_color_frame->SetBackgroundColor(Color3(55,55,55));

    parent_frame->AddChild(character_background_frame);
    parent_frame->SetGuiId("char_frame",character_background_frame);
    parent_frame->AddChild(hair_color_frame);
    parent_frame->AddChild(user_name_label);
    parent_frame->AddChild(user_name_text);
    parent_frame->AddChild(gender_label);
    parent_frame->AddChild(skin_label);
    parent_frame->AddChild(skin_name_label);
    parent_frame->AddChild(hair_label);
    parent_frame->AddChild(hair_name_label);
    parent_frame->AddChild(create_button);
    parent_frame->AddChild(cancel_button);
    parent_frame->AddChild(change_direction_left_button);
    parent_frame->AddChild(change_direction_right_button);
    parent_frame->AddChild(female_button);
    parent_frame->AddChild(male_button);
    parent_frame->AddChild(skin_left_button);
    parent_frame->AddChild(skin_right_button);
    parent_frame->AddChild(hair_left_button);
    parent_frame->AddChild(hair_right_button);
    parent_frame->SetBackgroundColor(Color3(255,255,255));

    //setup screen
    screen = new GuiScreen(parent_frame);
    screen->SetGuiId("parent_frame", parent_frame);
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


    return screen;
}
