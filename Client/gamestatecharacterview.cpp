#include "gamestatecharacterview.hpp"
#include "screenmaker.hpp"
#include "actordrawer.hpp"
#include "gamestatequit.hpp"

GameStateCharacterView::GameStateCharacterView(Game* game) : GameStateBase(game)
{

}

GameStateCharacterView::~GameStateCharacterView()
{

}

void GameStateCharacterView::Enter()
{
    PacketCharacterListRequest * datarequest = new PacketCharacterListRequest();
    this->game->SendPacket(datarequest);
}

void GameStateCharacterView::Exit()
{

}

void GameStateCharacterView::HandlePacket(PacketBase * packet)
{
    if(packet->GetType() == PacketBase::PACKET_CHARACTER)
    {
        PacketCharacter* returnCharacter = static_cast<PacketCharacter*>(packet);
        Character * PC = returnCharacter->GetCharacter();
        game->character_list.push_back(PC);
    }

}
void GameStateCharacterView::Tick()
{

}

void GameStateCharacterView::Render()
{
    this->game->DrawScreens();

    if(!game->character_list.empty())
    {
        ActorDrawer actordrawer;

        int num_chars = this->game->character_list.size();
        if (num_chars > 0)
        {
            GuiFrame* character_frame = static_cast<GuiFrame*>(this->game->GetCurrentScreen()->GetGuiById("character_frame_1"));
            GuiFrame* draw_frame = static_cast<GuiFrame*>(character_frame->GetGuiById("character_draw_area"));
            Vector2 draw_middle = draw_frame->GetAbsolutePosition() + draw_frame->GetSize()/2;

            actordrawer.DrawActor(this->game->character_list[0], draw_middle);
        }
        if (num_chars > 1)
        {
            GuiFrame* character_frame = static_cast<GuiFrame*>(this->game->GetCurrentScreen()->GetGuiById("character_frame_2"));
            GuiFrame* draw_frame = static_cast<GuiFrame*>(character_frame->GetGuiById("character_draw_area"));
            Vector2 draw_middle = draw_frame->GetAbsolutePosition() + draw_frame->GetSize()/2;

            actordrawer.DrawActor(this->game->character_list[1], draw_middle);
        }
    }
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
