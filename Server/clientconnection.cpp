#include "clientconnection.hpp"

#include <iostream>

ClientConnection::ClientConnection(Server* server, Address address, unsigned long int connection_id) :
    server(server), client_address(address), connection_id(connection_id), packet_sequence(0)
{

}

void ClientConnection::SendPacket(PacketBase* packet)
{
    packet->SetSequence(this->packet_sequence++);
    packet->SetAck(this->packet_ack);
    packet->SetAckBitfield(this->packet_ack_bitfield);

    this->packet_ack_list.push_back(PacketAck(packet, std::time(NULL)));

    this->server->SendPacketToAddress(packet, &(this->client_address));
}

void ClientConnection::ProcessPacket(PacketBase* packet)
{
    this->UpdatePacketAck(packet->GetSequence());

    if (packet->GetType() == PacketBase::PACKET_INIT)
    {
        PacketInitResponse packet;
        packet.AssignConnectionId(this->connection_id);

        this->SendPacket((PacketBase*)&packet);
    }
    else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
    {
        PacketDisconnectResponse packet;
        this->SendPacket((PacketBase*)&packet);
    }
    else if (packet->GetType() == PacketBase::PACKET_PING)
    {
        PacketPong packet;
        this->SendPacket((PacketBase*)&packet);
    }
}

// Update the clients current ack number from a received packet.
void ClientConnection::UpdatePacketAck(unsigned int sequence)
{
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

void ClientConnection::ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield)
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

void ClientConnection::TickPacketAcks()
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

                this->SendPacket((*first).packet);
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
