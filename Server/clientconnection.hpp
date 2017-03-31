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
    friend class ClientStatePlaying;

protected:
    unsigned int connection_id;
    unsigned int packet_sequence;

    PacketAckList ack_list;

    Address client_address;

    std::time_t last_communication;

    Server* server;

    Account* account;
    Character* playing_character;

    ClientStateBase* state;

    void DoAccountLogout();
    void FetchCharacterList();

    void DoCharacterLogout();
    void DoWarpCharacter(Map* map, Vector2 map_pos);

    void SendCharacterAppearance(Character* character);
    void SendCharacterPosition(Character* character);
    void SendCharacterMapEnter(Character* character);
    void SendCharacterMapLeave(Character* character);

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

    Character* GetPlayingCharacter();

};
#endif // CLIENTCONNECTION_HPP_INCLUDE
