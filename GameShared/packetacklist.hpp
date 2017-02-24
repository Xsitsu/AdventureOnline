#ifndef PACKETACKLIST_HPP_INCLUDE
#define PACKETACKLIST_HPP_INCLUDE

#include <ctime>
#include <list>

#include "packet.hpp"

struct PacketAck
{
    PacketBase* packet;
    std::time_t send_time;
<<<<<<< HEAD

    PacketAck(PacketBase* packet, std::time_t send_time) : packet(packet), send_time(send_time) {}
    PacketAck(const PacketAck& original) { send_time = original.send_time; packet = original.packet;}
    PacketAck& operator= (const PacketAck& rhs) { this->send_time = rhs.send_time; this->packet = rhs.packet; }
=======
>>>>>>> da960841c06c241b7078dd2f2bf4c51244bfe2f9
};

typedef std::list<PacketAck>::iterator ack_iter;

class DLL_EXPORT PacketAckList
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
