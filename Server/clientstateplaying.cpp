#include "clientstate.hpp"

ClientStatePlaying::ClientStatePlaying(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStatePlaying::~ClientStatePlaying()
{

}

void ClientStatePlaying::Enter()
{
    Character* character = this->client->playing_character;

    unsigned int map_id = 1;
    Vector2 map_pos = Vector2(5, 5);

    World* world = this->client->server->GetWorld();
    if (!world->IsMapLoaded(map_id))
    {
        world->LoadMap(map_id);
    }

    Map* map = world->GetMap(map_id);
    character->Warp(map, map_pos);

    PacketCharacterPosition* packet = new PacketCharacterPosition();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetMapId(map_id);
    packet->SetPositionX(map_pos.x);
    packet->SetPositionY(map_pos.y);
    packet->SetDirection(static_cast<uint8_t>(character->GetDirection()));

    this->client->SendPacket(packet);
}

void ClientStatePlaying::Exit()
{

}

bool ClientStatePlaying::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_LOGOUT)
    {
        this->client->DoAccountLogout();

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_DATA_REQUEST)
    {
        PacketCharacterDataRequest* request = static_cast<PacketCharacterDataRequest*>(packet);

        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;

            if (character->GetCharacterId() == request->GetCharacterId())
            {
                if (request->GetRequestAppearance())
                {
                    PacketCharacterAppearance* packet = new PacketCharacterAppearance();
                    packet->SetCharacterId(character->GetCharacterId());
                    packet->SetName(character->GetName());
                    packet->SetGender(static_cast<uint8_t>(character->GetGender()));
                    packet->SetSkin(static_cast<uint8_t>(character->GetSkin()));

                    this->client->SendPacket(packet);
                }
                if (request->GetRequestPosition())
                {
                    // Maybe eventually.
                }
                if (request->GetRequestStats())
                {
                    // Maybe eventually.
                }
            }
        }
        return true;
    }

    return false;
}
