#include "gamestatecharacterviewmake.hpp"

#include "gamestatecharacterview.hpp"

GuiFrame* CreateCharacterFrame(ALLEGRO_FONT* font)
{
    GuiFrame* base = new GuiFrame(Vector2(120, 240), Vector2(0, 0));
    base->SetBackgroundColor(Color3(124, 57, 21));

    GuiFrame* character_image = new GuiFrame(Vector2(120 - 20, 240 - 40 - font->height), Vector2(10, 20));
    character_image->SetBackgroundColor(Color3(0, 0, 0));

    GuiTextButton* character_name = new GuiTextButton(Vector2(120 - 20, font->height - 8), Vector2(10, 240 - font->height -4));
    character_name->SetText("Character");
    character_name->SetTextColor(Color3(255, 255, 255));
    character_name->SetBackgroundAlpha(0);
    character_name->SetTextFont(font);

    base->AddChild(character_image);
    base->AddChild(character_name);

    return base;
}

void GameStateCharacterViewMake::Enter()
{
    GuiFrame* base_frame;
    base_frame = new GuiFrame(Vector2(640, 480), Vector2(0, 0));
    base_frame->SetBackgroundColor(Color3(255, 255, 255));


    ALLEGRO_FONT* font = FontService::Instance()->GetFont("title_button");
    GuiFrame* character_frame = CreateCharacterFrame(font);
    character_frame->SetPosition(Vector2(200, 100));

    base_frame->AddChild(character_frame);

    GuiScreen* screen = new GuiScreen(base_frame);

    this->game->PushScreen(screen);

    this->game->ChangeState(new GameStateCharacterView(this->game));

}
