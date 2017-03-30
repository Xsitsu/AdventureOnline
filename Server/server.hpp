#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include <ctime>

#include "GameNetwork/socket.hpp"
#include "GameNetwork/packet.hpp"

#include "clientconnection.hpp"
#include "world.hpp"

#include "database.hpp"
#include "accountservice.hpp"

class ClientConnection;

class Server
{
protected:
    unsigned int connection_id_counter;

    std::time_t last_timeout_check;

    Socket socket;
    unsigned short port;

    const unsigned int max_connections;

    ClientConnection** clients;
    World* world;
    Database* database;

    AccountService accountservice;

    unsigned int FindOpenConnectionId();

public:
    Server(unsigned short port, unsigned int max_connections);
    ~Server();

    bool Init();
    void Tick();

    void EstablishDatabaseConnection();
    void CloseDatabaseConnection();
    Database* GetDatabaseConnection() const;

    PacketBase* ReceivePacket(Address& sender);
    void SendPacketToAddress(PacketBase* packet, Address* address);

    void TickPacketAcks();
    void TickClientTimeout();

    AccountService& GetAccountService();

    World* GetWorld();
};
#endif // SERVER_HPP_INCLUDE
