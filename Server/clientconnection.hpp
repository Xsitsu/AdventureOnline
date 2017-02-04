#ifndef CLIENTCONNECTION_HPP_INCLUDE
#define CLIENTCONNECTION_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"

#include "server.hpp"

class Server;


struct PacketAck
{
    PacketBase* packet;
    std::time_t send_time;

    PacketAck(PacketBase* packet, std::time_t send_time) : packet(packet), send_time(send_time) {}
};

typedef std::list<PacketAck>::iterator ack_iter;

class ClientConnection
{
protected:
    unsigned long int connection_id;
    unsigned int packet_sequence;
    unsigned int packet_ack;
    unsigned int packet_ack_bitfield;

    std::list<PacketAck> packet_ack_list;

    Address client_address;

    Server* server;

    void UpdatePacketAck(unsigned int sequence);
    void ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield);

public:
    ClientConnection(Server* server, Address address, unsigned long int connection_id);

    void SendPacket(PacketBase* packet);
    void ProcessPacket(PacketBase* packet);

    unsigned long int GetConnectionId() { return this->connection_id; }

    void TickPacketAcks();

};
#endif // CLIENTCONNECTION_HPP_INCLUDE
