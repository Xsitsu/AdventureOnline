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
    if (packet->GetType() == PacketBase::PACKET_CHARACTER_LIST)
    {
        PacketCharacterList* charlist_packet = static_cast<PacketCharacterList*>(packet);

        std::list<uint32_t> character_id_list = charlist_packet->GetCharacterList();
        std::list<uint32_t>::iterator iter;
        for (iter = character_id_list.begin(); iter != character_id_list.end(); ++iter)
        {
            PacketCharacterRequest* packet = new PacketCharacterRequest();
            packet->SetCharacterId(*iter);

            this->game->SendPacket(packet);
        }
    }
    else if(packet->GetType() == PacketBase::PACKET_CHARACTER)
    {
        PacketCharacter* return_character = static_cast<PacketCharacter*>(packet);
        Character* character = new Character();

        character->SetName(return_character->GetName());
        character->SetGender(static_cast<Character::Gender>(return_character->GetGender()));
        character->SetSkin(static_cast<Character::Skin>(return_character->GetSkin()));

        // ToDo: The rest eventually when they actually start to matter.
        // The actual data sent at this stage may change.

        game->character_list.push_back(character);
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
