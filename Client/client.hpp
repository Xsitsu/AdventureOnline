#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"

struct PacketAck
{
    PacketBase* packet;
    std::time_t send_time;

    PacketAck(PacketBase* packet, std::time_t send_time) : packet(packet), send_time(send_time) {}
};

typedef std::list<PacketAck>::iterator ack_iter;

class Client
{
protected:
    bool is_connected;

    unsigned long int connection_id;
    unsigned int packet_sequence;
    unsigned int packet_ack;
    unsigned int packet_ack_bitfield;

    unsigned short listen_port;

    std::list<PacketAck> packet_ack_list;

    Socket socket;
    Address server_address;

    void InternalSendPacket(PacketBase* packet);
    PacketBase* InternalReceivePacket();

    void UpdatePacketAck(unsigned int sequence);
    void ConfirmPacketAcks(unsigned int ack, unsigned int ack_bitfield);

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
