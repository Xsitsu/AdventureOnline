#include "screenmaker.hpp"

GuiFrame* CreateBarFrame(Color3 main_bar_color)
{
    Color3 bar_base_color = Color3(180, 180, 180);
    Vector2 bar_base_rounding = Vector2(4, 4);
    char bar_base_alpha = 160;

    GuiFrame* bar_frame = new GuiFrame(Vector2(120, 40), Vector2(0, 0));
    bar_frame->SetBackgroundAlpha(0);

    GuiTextLabel* bar_text = new GuiTextLabel(Vector2(116, 14), Vector2(4, 0));
    bar_text->SetBackgroundAlpha(0);
    bar_text->SetTextFont(FontService::Instance()->GetFont("stat_bar"));
    bar_text->SetText("Stat: XX");
    bar_text->SetTextColor(Color3(255, 255, 255));

    GuiFrame* bar_base = new GuiFrame(Vector2(112, 26), Vector2(4, 14));
    bar_base->SetBackgroundColor(bar_base_color);
    bar_base->SetRounding(bar_base_rounding);
    bar_base->SetBackgroundAlpha(bar_base_alpha);

    GuiFrame* bar_main = new GuiFrame(Vector2(112, 26), Vector2(4, 14));
    bar_main->SetRounding(bar_base_rounding);
    bar_main->SetBackgroundColor(main_bar_color);

    bar_frame->AddChild(bar_text);
    bar_frame->AddChild(bar_base);
    bar_frame->AddChild(bar_main);

    bar_frame->SetGuiId("bar_text", bar_text);
    bar_frame->SetGuiId("bar_main", bar_main);

    return bar_frame;
}

GuiScreen* ScreenMakerPlaying::MakeScreen()
{
    GuiFrame* base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundAlpha(0);

    GuiFrame* bar_frame_base = new GuiFrame(Vector2(640, 40), Vector2(0, 480 - 40));
    bar_frame_base->SetBackgroundAlpha(120);

    GuiFrame* bar_frame_health = CreateBarFrame(Color3(255, 36, 52));

    bar_frame_base->AddChild(bar_frame_health);

    base_frame->AddChild(bar_frame_base);


    GuiScreen* screen = new GuiScreen(base_frame);

    return screen;
}
