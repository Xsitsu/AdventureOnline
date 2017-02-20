#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"
#include "GameShared/packetacklist.hpp"

class Client
{
    const int CONNECTION_TIMEOUT = 5;

protected:
    bool is_connected;

    unsigned int connection_id;
    unsigned int packet_sequence;

    unsigned short listen_port;

    PacketAckList ack_list;

    Socket socket;
    Address server_address;

    std::time_t last_communication;

    void InternalSendPacket(PacketBase* packet);
    PacketBase* InternalReceivePacket();

public:
    Client(Address address);

    bool Init(unsigned short listen_port);

    bool SendConnectRequest();
    bool GetConnectResponse();

    bool SendDisconnectRequest();
    void FinalizeDisconnect();
    void DoDisconnect();

    void Cleanup();

    bool IsConnected() { return this->is_connected; }

    void SendPacket(PacketBase* packet);
    PacketBase* ReceivePacket();

    void TickPacketAcks();
    bool CheckForTimeout();
};
#endif // CLIENT_HPP_INCLUDE
