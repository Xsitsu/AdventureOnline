#include "client.hpp"

#include <iostream>

Client::Client(Address address) : is_connected(false), connection_id(0),
packet_sequence(0), server_address(address), last_communication(0)

{}

bool Client::Init(unsigned short listen_port)
{
    if(this->socket.IsOpen()) return false;

    this->socket.Open(listen_port);
    if (!this->socket.IsOpen()) return false;

    this->listen_port = listen_port;

    return true;
}

bool Client::SendConnectRequest()
{
    if (this->is_connected) return false;

    PacketInit* packet = new PacketInit();
    packet->SetListenPort(this->listen_port);
    this->InternalSendPacket(packet);

    return true;
}

bool Client::GetConnectResponse()
{
    if (this->is_connected) return false;

    bool ret_val = false;
    PacketBase* response = this->InternalReceivePacket();
    if (response)
    {
        if (response->GetType() == PacketBase::PACKET_INIT_RESPONSE)
        {
            ret_val = true;

            PacketInitResponse* res = (PacketInitResponse*)response;
            if (res->GetConnectionAccepted())
            {
                this->connection_id = res->GetAssignedConnectionId();
                this->is_connected = true;

                std::cout << "Connected!" << std::endl;
            }
            else
            {
                std::cout << "Connection Refused!" << std::endl;
            }
        }

        delete response;
    }

    return ret_val;
}

bool Client::SendDisconnectRequest()
{
    if (!this->is_connected) return false;

    PacketDisconnect* packet = new PacketDisconnect();
    this->InternalSendPacket(packet);

    return true;
}

void Client::FinalizeDisconnect()
{
    if (!this->is_connected) return;

    this->DoDisconnect();
    std::cout << "Disconnected!" << std::endl;
}

void Client::DoDisconnect()
{
    this->is_connected = false;
}

void Client::Cleanup()
{
    if(this->socket.IsOpen())
    {
        this->socket.Close();
    }
}

void Client::InternalSendPacket(PacketBase* packet)
{
    packet->SetConnectionId(this->connection_id);
    packet->SetSequence(this->packet_sequence++);
    packet->SetAck(this->ack_list.GetPacketAck());
    packet->SetAckBitfield(this->ack_list.GetPacketAckBitfield());

    char buffer[PacketBase::MAX_BUFFER];
    unsigned int data_size = packet->Encode(buffer);

    this->socket.Send(this->server_address, buffer, data_size);

    if (packet->GetNeedsAck())
    {
        this->ack_list.RegisterPacket(packet);
    }
    else
    {
        delete packet;
    }
}

PacketBase* Client::InternalReceivePacket()
{
    Address sender;
    char buffer[PacketBase::MAX_BUFFER];

    int bytes_read = 0;
    PacketBase* packet = NULL;

    bool reading = true;
    while (reading)
    {
        bytes_read = socket.Receive(sender, buffer, sizeof(buffer));

        if (bytes_read <= 0)
        {
            reading = false;
        }
        else if (sender.GetAddress() == this->server_address.GetAddress())
        {
            PacketReader reader;
            packet = reader.ReadPacket(buffer, bytes_read);
            if (packet)
            {
                reading = false;
                this->last_communication = std::time(NULL);

                this->ack_list.UpdatePacketAck(packet->GetSequence());
                this->ack_list.ConfirmPacketAcks(packet->GetAck(), packet->GetAckBitfield());
            }
            else
            {
                std::cout << "Presumed to read junk data from server." << std::endl;
            }
        }
        else
        {
            std::cout << "Got something from NOT the server." << std::endl;
            std::cout << "Sender: " << sender.GetAddress() << " : " << sender.GetPort() << std::endl;
            std::cout << "Server Address: " << this->server_address.GetAddress() << " : " << this->server_address.GetPort() << std::endl;
        }
    }

    return packet;
}

void Client::SendPacket(PacketBase* packet)
{
    if (this->is_connected)
    {
        this->InternalSendPacket(packet);
    }
    else
    {
        delete packet;
    }
}

PacketBase* Client::ReceivePacket()
{
    if (this->is_connected)
    {
        return this->InternalReceivePacket();
    }
    return NULL;
}

bool Client::CheckForTimeout()
{
    return (std::time(NULL) - this->last_communication > this->CONNECTION_TIMEOUT);
}

void Client::TickPacketAcks()
{
    std::list<PacketBase*> resend_list = this->ack_list.TickPacketAcks();
    while (!resend_list.empty())
    {
        this->InternalSendPacket(resend_list.front());
        resend_list.pop_front();
    }
}
