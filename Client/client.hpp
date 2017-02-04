#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"
#include "GameShared/packetacklist.hpp"

class Client
{
protected:
    bool is_connected;

    unsigned int connection_id;
    unsigned int packet_sequence;

    unsigned short listen_port;

    PacketAckList ack_list;

    Socket socket;
    Address server_address;

    void InternalSendPacket(PacketBase* packet);
    PacketBase* InternalReceivePacket();

public:
    Client(Address address);

    bool Init(unsigned short listen_port);
    bool SendConnectRequest();
    bool GetConnectResponse();
    void Disconnect();

    bool IsConnected() { return this->is_connected; }

    void SendPacket(PacketBase* packet);
    PacketBase* ReceivePacket();

    void TickPacketAcks();
};
#endif // CLIENT_HPP_INCLUDE
