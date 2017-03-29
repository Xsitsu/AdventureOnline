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
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            PacketCharacter* packet = new PacketCharacter(*iter);
            this->client->SendPacket(packet);
        }
        return true;
    }


    return false;
}
