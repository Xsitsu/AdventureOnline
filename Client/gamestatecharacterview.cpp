#include "gamestatecharacterview.hpp"
#include "screenmaker.hpp"

#include "gamestatequit.hpp"

GameStateCharacterView::GameStateCharacterView(Game* game) : GameStateBase(game)
{

}

GameStateCharacterView::~GameStateCharacterView()
{

}

void GameStateCharacterView::Enter()
{

}

void GameStateCharacterView::Exit()
{

}

void GameStateCharacterView::HandlePacket(PacketBase * packet)
{
    PacketCharacter* returnCharacter = static_cast<PacketCharacter*>(packet);
    Character * PC = returnCharacter->GetCharacter();
    game->character_list.push_back(PC);

    for(unsigned int i = 0; i < game->character_list.size(); i++)
    {
        std::cout << game->character_list[i]->GetName() << std::endl;
    }

//    std::cout << "PacketCharacter Recieved:\t" << character->GetCharacters().GetName() << std::endl;
//    this->game->PopScreen();
//    this->game->PopScreen();
//    this->game->PopScreen();
//    ScreenMakerCharacterView maker(this->game);
//    GuiScreen* screen = maker.MakeScreen();
//
//    this->game->PushScreen(screen);
}
void GameStateCharacterView::Tick()
{

}

void GameStateCharacterView::Render()
{
    this->game->DrawScreens();
}

void GameStateCharacterView::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateCharacterView::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}

void GameStateCharacterView::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}

void GameStateCharacterView::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateCharacterView::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
