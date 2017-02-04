#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include <unordered_map>

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"

#include "clientconnection.hpp"

class ClientConnection;

class Server
{
protected:
    unsigned long int connection_id_counter;

    Socket socket;
    unsigned short port;

    std::unordered_map<unsigned long int, ClientConnection*> clients;

public:
    Server(unsigned short port);

    bool Init();
    void Tick();

    PacketBase* ReceivePacket(Address& sender);
    void SendPacketToAddress(PacketBase* packet, Address* address);

};
#endif // SERVER_HPP_INCLUDE
