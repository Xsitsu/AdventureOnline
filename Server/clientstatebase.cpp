#include "clientstate.hpp"

bool ClientStateBase::ProcessPacket(PacketBase* packet)
{
    if (packet->GetType() == PacketBase::PACKET_PING)
    {
        PacketPong* packet = new PacketPong();
        packet->SetNeedsAck(false);
        this->client->SendPacket(packet);

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
    {
        PacketDisconnectResponse* packet = new PacketDisconnectResponse();
        packet->SetNeedsAck(false);
        this->client->SendPacket(packet);

        return true;
    }

    return false;
}
