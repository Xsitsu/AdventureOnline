#ifndef PACKETACKLIST_HPP_INCLUDE
#define PACKETACKLIST_HPP_INCLUDE

#include <ctime>
#include <list>

#include "packet.hpp"

struct PacketAck
{
    PacketBase* packet;
    std::time_t send_time;
};

typedef std::list<PacketAck>::iterator ack_iter;

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketAckList
{
protected:
    unsigned int packet_ack;
    unsigned int packet_ack_bitfield;

    std::list<PacketAck> packet_ack_list;

public:
    PacketAckList();
    ~PacketAckList();

    unsigned int GetPacketAck() { return this->packet_ack; }
    unsigned int GetPacketAckBitfield() { return this->packet_ack_bitfield; }

    void UpdatePacketAck(unsigned int sequence);
    void ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield);
    std::list<PacketBase*> TickPacketAcks();
    void RegisterPacket(PacketBase* packet);

};
#endif // PACKETACKLIST_HPP_INCLUDE
