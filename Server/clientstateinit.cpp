#include "clientstate.hpp"

ClientStateInit::ClientStateInit(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStateInit::~ClientStateInit()
{

}

void ClientStateInit::Enter()
{

}

void ClientStateInit::Exit()
{

}

bool ClientStateInit::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_INIT)
    {
        PacketInitResponse* packet = new PacketInitResponse();
        packet->AssignConnectionId(this->client->connection_id);

        this->client->SendPacket(packet);

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }

    return false;
}
