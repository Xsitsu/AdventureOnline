#include "gamestatecharactercreation.hpp"
#include "actordrawer.hpp"

GameStateCharacterCreation::GameStateCharacterCreation(Game * game): GameStateBase(game)
{
    //ctor
}

GameStateCharacterCreation::~GameStateCharacterCreation()
{
    //dtor
}



void GameStateCharacterCreation::Enter()
{
    std::cout << "test 'cuz I have no clue what to do" << std::endl;
}
void GameStateCharacterCreation::Exit()
{

}
void GameStateCharacterCreation::Tick()
{
    std::cout << "tick" << std::endl;
    Character * pc = game->current_character;
    pc->Update();
    if(!pc->IsMoving())
    {
        pc->ChangeState(new ActorStateWalk(pc));
    }
}
void GameStateCharacterCreation::Render()
{
    this->game->DrawScreens();
    if(this->game->GetCurrentCharacter())
    {
        ActorDrawer actordraw;
        GuiFrame * parent = static_cast<GuiFrame*>(game->GetCurrentScreen()->GetGuiById("parent_frame"));
        GuiFrame * charframe = static_cast<GuiFrame*>(parent->GetGuiById("char_frame"));
        Vector2 draw_middle = charframe->GetAbsolutePosition() + charframe->GetSize()/2;
        actordraw.DrawActor(this->game->GetCurrentCharacter(), draw_middle);
    }
}

void GameStateCharacterCreation::HandleKeyDown(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}
void GameStateCharacterCreation::HandleKeyUp(const ALLEGRO_KEYBOARD_EVENT& keyboard)
{

}
void GameStateCharacterCreation::HandleMouseMove(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}
void GameStateCharacterCreation::HandleMouseDown(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}
void GameStateCharacterCreation::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseMove(pos);
}
void GameStateCharacterCreation::HandlePacket(PacketBase * packet)
{

}

