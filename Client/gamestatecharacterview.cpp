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
        game->PopScreen();

        ScreenMakerCharacterView maker(game);
        game->PushScreen(maker.MakeScreen());
    }

}
void GameStateCharacterView::Tick()
{

}

void GameStateCharacterView::Render()
{
    ActorDrawer actorDrawer;
    Vector2 draw_pos(300,50);
    this->game->DrawScreens();
    if(!game->character_list.empty())
    {
        for(unsigned int i = 0; i < game->character_list.size() && i < 2; i++)
        {
            DrawSpecs specs = actorDrawer.GetDrawSpecs(game->character_list[i]);
            al_draw_tinted_bitmap_region(specs.bitmap, specs.tint,
                                         specs.sprite_start.x, specs.sprite_start.y,
                                         specs.sprite_size.x, specs.sprite_size.y,
                                         draw_pos.x, draw_pos.y+190*i, specs.draw_flags);
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
