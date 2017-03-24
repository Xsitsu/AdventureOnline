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


    return false;
}
