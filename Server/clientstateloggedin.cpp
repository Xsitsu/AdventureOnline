#include "clientstate.hpp"
#include "GameWorld/character.hpp"

ClientStateLoggedIn::ClientStateLoggedIn(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStateLoggedIn::~ClientStateLoggedIn()
{

}

void ClientStateLoggedIn::Enter()
{

}

void ClientStateLoggedIn::Exit()
{

}

bool ClientStateLoggedIn::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_LOGOUT)
    {
        this->client->DoAccountLogout();

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }
    else if(packet->GetType() == PacketBase::PACKET_CHARACTER_LIST_REQUEST)
    {
        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<uint32_t> character_ids;
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;
            uint32_t id = character->GetCharacterId();
            character_ids.push_back(id);
        }

        PacketCharacterList* packet = new PacketCharacterList();
        packet->SetCharacterList(character_ids);

        this->client->SendPacket(packet);

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
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_LOGIN)
    {
        PacketCharacterLogin* login_packet = static_cast<PacketCharacterLogin*>(packet);
        unsigned int character_id = login_packet->GetCharacterId();

        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;
            if (character->GetCharacterId() == character_id)
            {
                this->client->account->SetPlayingCharacter(character);
            }
        }

        return true;
    }

    return false;
}
