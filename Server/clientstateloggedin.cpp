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
        this->client->server->GetAccountService().UnregisterAccount(this->client->account->GetAccountId());

        delete this->client->account;
        this->client->account = nullptr;

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }
    else if(packet->GetType() == PacketBase::PACKET_CHARACTERS_LIST_REQUEST)
    {
        Database * database = this->client->server->GetDatabaseConnection();
        Character * playerCharacter = nullptr;
        PacketCharacter * returnCharacter = nullptr;
        vector<int> characters = database->ReadPlayerCharacters(client->account->GetEmail());
        vector<int>::iterator it = characters.begin();
        while(it < characters.end())
        {
           playerCharacter = database->ReadCharacterInfo( *it++);
           returnCharacter = new PacketCharacter(playerCharacter);
           client->SendPacket(returnCharacter);
           delete playerCharacter;
        }

        return true;
    }


    return false;
}
