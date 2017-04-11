#include "gamestatecharactercreation.hpp"
#include "actordrawer.hpp"
GameStateCharacterCreation::GameStateCharacterCreation(Game* game) : GameStateBase(game)
{

}

GameStateCharacterCreation::~GameStateCharacterCreation()
{

}

void GameStateCharacterCreation::HandlePacket(PacketBase* packet)
{

}

void GameStateCharacterCreation::Enter()
{

}

void GameStateCharacterCreation::Exit()
{

}

void GameStateCharacterCreation::Tick()
{
    Character * pc = game->current_character;
    if(pc)
    {
        pc->Update();
        if(!pc->IsMoving())
        {
            pc->ChangeState(new ActorStateWalk(pc));
        }
    }
}

void GameStateCharacterCreation::Render()
{
    this->game->DrawScreens();
    if(this->game->GetCurrentCharacter())
    {
        ActorDrawer actordraw;
        GuiFrame * charframe = static_cast<GuiFrame*>(game->GetCurrentScreen()->GetGuiById("char_frame"));
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
    this->game->GetCurrentScreen()->HandleMouseDown(pos);
}

void GameStateCharacterCreation::HandleMouseUp(const ALLEGRO_MOUSE_EVENT& mouse)
{
    Vector2 pos(mouse.x, mouse.y);
    this->game->GetCurrentScreen()->HandleMouseUp(pos);
}
