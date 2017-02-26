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
    const int CONNECTION_TIMEOUT = 5;

protected:
    unsigned int connection_id;
    unsigned int packet_sequence;

    PacketAckList ack_list;

    Address client_address;

    std::time_t last_communication;

    Server* server;

public:
    ClientConnection(Server* server, Address address, unsigned int connection_id);

    void SendPacket(PacketBase* packet);
    void ProcessPacket(PacketBase* packet);

    unsigned int GetConnectionId() { return this->connection_id; }

    void TickPacketAcks();
    bool CheckForTimeout();
    void UpdateLastCommunicationTime();
};
#endif // CLIENTCONNECTION_HPP_INCLUDE
