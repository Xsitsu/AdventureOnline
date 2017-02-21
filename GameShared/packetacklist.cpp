#include "packetacklist.hpp"

#include <iostream>

PacketAckList::PacketAckList() : packet_ack(0), packet_ack_bitfield(0), packet_ack_list(std::list<PacketAck>())
{}

PacketAckList::~PacketAckList()
{
    while (!this->packet_ack_list.empty())
    {
        delete this->packet_ack_list.front().packet;
        this->packet_ack_list.pop_front();
    }
}

void PacketAckList::UpdatePacketAck(unsigned int sequence)
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

void PacketAckList::ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield)
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

std::list<PacketBase*> PacketAckList::TickPacketAcks()
{
    std::list<PacketBase*> resend_list;

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

                resend_list.push_back((*first).packet);
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

    return resend_list;
}

void PacketAckList::RegisterPacket(PacketBase* packet)
{
    this->packet_ack_list.push_back(PacketAck(packet, std::time(NULL)));
}
