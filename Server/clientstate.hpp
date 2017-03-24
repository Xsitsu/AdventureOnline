#ifndef CLIENTSTATE_HPP_INCLUDE
#define CLIENTSTATE_HPP_INCLUDE

#include <iostream>

class ClientConnection;

#include "clientconnection.hpp"
#include "GameNetwork/packet.hpp"

class ClientStateBase
{
protected:
    ClientConnection* client;

public:
    ClientStateBase(ClientConnection* client) : client(client) {}
    virtual ~ClientStateBase() {}

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual bool ProcessPacket(PacketBase* packet);
};



class ClientStateInit : public ClientStateBase
{
protected:

public:
    ClientStateInit(ClientConnection* client);
    ~ClientStateInit();

    void Enter();
    void Exit();
    bool ProcessPacket(PacketBase* packet);
};


class ClientStateNoLogin : public ClientStateBase
{
protected:

public:
    ClientStateNoLogin(ClientConnection* client);
    ~ClientStateNoLogin();

    void Enter();
    void Exit();
    bool ProcessPacket(PacketBase* packet);
};

class ClientStateLoggedIn : public ClientStateBase
{
protected:

public:
    ClientStateLoggedIn(ClientConnection* client);
    ~ClientStateLoggedIn();

    void Enter();
    void Exit();
    bool ProcessPacket(PacketBase* packet);
};

#endif // CLIENTSTATE_HPP_INCLUDE
