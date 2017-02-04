#include "client.hpp"

#include <iostream>

Client::Client(Address address) : is_connected(false), server_address(address),
connection_id(0), packet_sequence(0), packet_ack(0), packet_ack_bitfield(0)
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

    PacketBase* response = this->InternalReceivePacket();
    if (response)
    {
        if (response->GetType() == PacketBase::PACKET_INIT_RESPONSE)
        {
            PacketInitResponse* res = (PacketInitResponse*)response;
            this->connection_id = res->GetAssignedConnectionId();
            this->is_connected = true;

            std::cout << "Connected!" << std::endl;
        }

        delete response;
    }

    return this->is_connected;
}

void Client::Disconnect()
{
    if (this->is_connected)
    {
        PacketDisconnect packet = PacketDisconnect();
        this->InternalSendPacket((PacketBase*)&packet);

        PacketBase* response = NULL;

        bool wait_for_response = true;
        while (wait_for_response)
        {
            std::cout << "Waiting for response..." << std::endl;

            response = this->InternalReceivePacket();
            if (response)
            {
                if (response->GetType() == PacketBase::PACKET_DISCONNECT_RESPONSE)
                {
                    wait_for_response = false;
                }

                delete response;
            }
        }
        std::cout << "Disconnected!" << std::endl;

        this->is_connected = false;
        this->socket.Close();
    }
}

void Client::InternalSendPacket(PacketBase* packet)
{
    packet->SetConnectionId(this->connection_id);
    packet->SetSequence(this->packet_sequence++);
    packet->SetAck(this->packet_ack);
    packet->SetAckBitfield(this->packet_ack_bitfield);

    this->packet_ack_list.push_back(PacketAck(packet, std::time(NULL)));

    char buffer[PacketBase::MAX_BUFFER];
    unsigned int data_size = packet->Encode(buffer);

    this->socket.Send(this->server_address, buffer, data_size);
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

                this->UpdatePacketAck(packet->GetSequence());
                this->ConfirmPacketAcks(packet->GetAck(), packet->GetAckBitfield());
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

// Update the clients current ack number from a received packet.
void Client::UpdatePacketAck(unsigned int sequence)
{
    std::cout << "Ack'ing packet: " << sequence << std::endl;

    long int diff = (long int)sequence - (long int)this->packet_ack;
    this->packet_ack = sequence;
    if (diff > 0)
    {
        unsigned int bitfield = this->packet_ack_bitfield << 1;
        bitfield | 1;
        bitfield << (diff - 1);

        this->packet_ack_bitfield = bitfield;
    }
    else if (diff < 0)
    {
        unsigned int bitfield_adder = 1 << ((-diff) - 1);
        this->packet_ack_bitfield = this->packet_ack_bitfield | bitfield_adder;
    }
}

// Update client's packet ack list from the ack and ack bitfield from a received packet.
void Client::ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield)
{
    std::cout << "Packet was ack'd: " << ack << std::endl;

    if (!this->packet_ack_list.empty())
    {
        ack_iter iter = this->packet_ack_list.begin();

        //for(first; first!=last; ++first)
        while (iter != this->packet_ack_list.end())
        {
            unsigned int check_sequence = (*iter).packet->GetSequence();
            long int diff = (long int)ack - (long int)check_sequence;

            bool was_acked = false;
            if (diff == 0)
            {
                was_acked = true;
            }
            else if (diff > 0)
            {
                long int shift = diff - 1;
                was_acked = (((ack_bitfield >> shift) & 1) == 1);
            }

            if (was_acked)
            {
                delete (*iter).packet;
                ack_iter del_index = iter++;
                this->packet_ack_list.erase(del_index);
            }
            else
            {
                ++iter;
            }
        }
    }
}

void Client::SendPacket(PacketBase* packet)
{
    if (this->is_connected)
    {
        this->InternalSendPacket(packet);
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

void Client::TickPacketAcks()
{
    if (!this->packet_ack_list.empty())
    {
        std::time_t cur_time = std::time(NULL);

        ack_iter first = this->packet_ack_list.begin();

        unsigned int resend_packet_count = 0;
        for(first; first!=this->packet_ack_list.end(); ++first)
        {
            std::time_t diff = cur_time - (*first).send_time;
            if (diff > 1)
            {
                std::cout << "Didn't receive ack. Resending packet!" << std::endl;
                resend_packet_count++;

                this->InternalSendPacket((*first).packet);
            }
            else
            {
                break;
            }
        }

        for (unsigned int i = 0; i < resend_packet_count; i++)
        {
            this->packet_ack_list.pop_front();
        }
    }
}
