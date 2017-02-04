#ifndef CLIENTCONNECTION_HPP_INCLUDE
#define CLIENTCONNECTION_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"
#include "GameShared/packetacklist.hpp"

#include "server.hpp"

class Server;

class ClientConnection
{
protected:
    unsigned long int connection_id;
    unsigned int packet_sequence;

    PacketAckList ack_list;

    Address client_address;

    Server* server;

public:
    ClientConnection(Server* server, Address address, unsigned long int connection_id);

    void SendPacket(PacketBase* packet);
    void ProcessPacket(PacketBase* packet);

    unsigned long int GetConnectionId() { return this->connection_id; }

    void TickPacketAcks();

};
#endif // CLIENTCONNECTION_HPP_INCLUDE
