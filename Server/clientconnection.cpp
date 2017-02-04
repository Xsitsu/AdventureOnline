#include "clientconnection.hpp"

#include <iostream>

ClientConnection::ClientConnection(Server* server, Address address, unsigned long int connection_id) :
    server(server), client_address(address), connection_id(connection_id), packet_sequence(0)
{

}

void ClientConnection::SendPacket(PacketBase* packet)
{
    packet->SetSequence(this->packet_sequence++);
    packet->SetAck(this->ack_list.GetPacketAck());
    packet->SetAckBitfield(this->ack_list.GetPacketAckBitfield());

    this->ack_list.RegisterPacket(packet);

    this->server->SendPacketToAddress(packet, &(this->client_address));
}

void ClientConnection::ProcessPacket(PacketBase* packet)
{
    this->ack_list.UpdatePacketAck(packet->GetSequence());
    this->ack_list.ConfirmPacketAcks(packet->GetAck(), packet->GetAckBitfield());

    if (packet->GetType() == PacketBase::PACKET_INIT)
    {
        PacketInitResponse* packet = new PacketInitResponse();
        packet->AssignConnectionId(this->connection_id);

        this->SendPacket(packet);
    }
    else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
    {
        this->SendPacket(new PacketDisconnectResponse());
    }
    else if (packet->GetType() == PacketBase::PACKET_PING)
    {
        this->SendPacket(new PacketPong());
    }
}

void ClientConnection::TickPacketAcks()
{
    std::list<PacketBase*> resend_list = this->ack_list.TickPacketAcks();
    while (!resend_list.empty())
    {
        this->SendPacket(resend_list.front());
        resend_list.pop_front();
    }
}
