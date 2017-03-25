#include "clientstate.hpp"

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
        else if(packet->GetType() == PacketBase::PACKET_DATA_REQUEST)
    {
//        Database * database = this->server->GetDatabaseConnection();
//        PacketCharacter * returnCharacter = new PacketCharacter();
//        vector<int> characters = database->ReadePlayerCharacters(account->GetEmail());
//        vector<int>::iterator it = characters.begin();
//        while(it < characters.end())
//        {
//           returnCharacter->SetCharacters(database->ReadCharacterInfo( *it++) );
//           this->SendPacket(returnCharacter);
//           returnCharacter = new PacketCharacter();
//        }

        return true;
    }


    return false;
}
