#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include <ctime>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"

#include "clientconnection.hpp"

class ClientConnection;

class Server
{
protected:
    unsigned int connection_id_counter;

    std::time_t last_timeout_check;

    Socket socket;
    unsigned short port;

    const unsigned int max_connections;

    //std::unordered_map<unsigned long int, ClientConnection*> clients;
    ClientConnection** clients;

    unsigned int FindOpenConnectionId();

public:
    Server(unsigned short port, unsigned int max_connections);
    ~Server();

    bool Init();
    void Tick();

    PacketBase* ReceivePacket(Address& sender);
    void SendPacketToAddress(PacketBase* packet, Address* address);

    void TickPacketAcks();
    void TickClientTimeout();
};
#endif // SERVER_HPP_INCLUDE
