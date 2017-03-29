#ifndef CLIENTCONNECTION_HPP_INCLUDE
#define CLIENTCONNECTION_HPP_INCLUDE

#include <ctime>
#include <list>

#include "GameNetwork/socket.hpp"
#include "GameNetwork/packet.hpp"
#include "GameNetwork/packetacklist.hpp"

#include "server.hpp"
#include "account.hpp"

#include "clientstate.hpp"

class ClientStateBase;

class Server;

class ClientConnection
{
    const int CONNECTION_TIMEOUT = 5;

    friend class ClientStateBase;
    friend class ClientStateInit;
    friend class ClientStateNoLogin;
    friend class ClientStateLoggedIn;

protected:
    unsigned int connection_id;
    unsigned int packet_sequence;

    PacketAckList ack_list;

    Address client_address;

    std::time_t last_communication;

    Server* server;

    Account* account;

    ClientStateBase* state;

    void DoAccountLogout();
    void FetchCharacterList();

public:
    ClientConnection(Server* server, Address address, unsigned int connection_id);
    ~ClientConnection();

    void SendPacket(PacketBase* packet);
    void ProcessPacket(PacketBase* packet);

    unsigned int GetConnectionId() { return this->connection_id; }

    void TickPacketAcks();
    bool CheckForTimeout();
    void UpdateLastCommunicationTime();

    void ChangeState(ClientStateBase* state);

};
#endif // CLIENTCONNECTION_HPP_INCLUDE
