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

    std::list<ClientConnection*> clients_list;
    ClientConnection** clients;
    World* world;
    Database* database;

    AccountService accountservice;

    unsigned int FindOpenConnectionId();

    void ConnectClient(ClientConnection* client);
    void DisconnectClient(ClientConnection* client);

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

    std::list<ClientConnection*> GetClientList() const;
};
#endif // SERVER_HPP_INCLUDE
