#include "server.hpp"

#include <iostream>

Server::Server(unsigned short port, unsigned int max_connections) : connection_id_counter(0),
last_timeout_check(std::time(NULL)), port(port), max_connections(max_connections), world(NULL), database(NULL)
{
    clients = new ClientConnection*[this->max_connections];
    for (unsigned int i = 0; i < this->max_connections; i++)
    {
        clients[i] = NULL;
    }
}

Server::~Server()
{
    delete[] clients;
    delete[] world;
}

unsigned int Server::FindOpenConnectionId()
{
    unsigned int start = this->connection_id_counter;
    unsigned int id = start;
    unsigned int max = this->max_connections;

    while (this->clients[id] != NULL)
    {
        //std::cout << "Scanning: " << id << "/" << max << std::endl;

        id++;
        if (id >= max)
        {
            id -= max;
        }

        if (id == start)
        {
            //std::cout << "No open connections!" << std::endl;
            throw "fail";
        }
    }

    this->connection_id_counter = id + 1;

    if (this->connection_id_counter >= max)
    {
        this->connection_id_counter -= max;
    }

    std::cout << "Returning Connection Id: " << id << std::endl;
    return id;
}

bool Server::Init()
{
    if(this->socket.IsOpen()) return false;

    this->socket.Open(this->port, true);
    if (!this->socket.IsOpen()) return false;

    this->world = new World(2);

    return true;
}

void Server::Tick()
{
    Address sender;
    PacketBase* packet = this->ReceivePacket(sender);
    while (packet)
    {
        //std::cout << "Got a packet. [" << packet->GetSequence() << "]" << std::endl;

        ClientConnection* client = NULL;
        if (packet->GetType() == PacketBase::PACKET_INIT)
        {
            //std::cout << "PacketInit" << std::endl;
            unsigned short listen_port = static_cast<PacketInit*>(packet)->GetListenPort();
            Address clientAddress(sender.GetAddress(), listen_port);

            unsigned int con_id = 0;
            try
            {
                con_id = this->FindOpenConnectionId();
            }
            catch (...)
            {
                std::cout << "Refusing connection start counting at: " << this->connection_id_counter << std::endl;
                PacketInitResponse* res = new PacketInitResponse();
                res->SetConnectionAccepted(false);
                this->SendPacketToAddress(res, &clientAddress);
                delete res;
                return;
            }

            client = new ClientConnection(this, clientAddress, con_id);
            this->ConnectClient(client);

            std::cout << "New client connected with id: " << con_id << std::endl;
        }
        else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
        {
            //std::cout << "PacketDisconnect" << std::endl;
            unsigned long int con_id = packet->GetConnectionId();
            client = this->clients[con_id];

            if (!client) return;

            client->ProcessPacket(packet);

            delete packet;
            this->DisconnectClient(client);

            std::cout << "Client disconnected with id: " << con_id << std::endl;

            return;
        }
        else
        {
//            std::cout << "OtherPacket: " << packet->GetType() << std::endl;

            unsigned int connection_id = packet->GetConnectionId();
            client = this->clients[connection_id];
        }

        if (client)
        {
            client->UpdateLastCommunicationTime();
            client->ProcessPacket(packet);
        }
        else
        {
            std::cout << "Client didn't exist with expected id: " << packet->GetConnectionId() << std::endl;
        }

        delete packet;
        packet = this->ReceivePacket(sender);
    }

    this->TickPacketAcks();

    std::time_t time_tick = std::time(NULL);
    if (time_tick - this->last_timeout_check >= 2)
    {
        this->last_timeout_check = time_tick;
        this->TickClientTimeout();
    }
}

PacketBase* Server::ReceivePacket(Address& sender)
{
    char buffer[PacketBase::MAX_BUFFER];

    int bytes_read = 0;
    PacketBase* packet = NULL;

    bool reading = true;
    while (reading)
    {
        bytes_read = socket.Receive(sender, buffer, sizeof(buffer));

        if (bytes_read <= 0)
        {
            reading = false;
        }
        else
        {
            PacketReader reader;
            packet = reader.ReadPacket(buffer, bytes_read);
            if (packet)
            {
                reading = false;
            }
            else
            {
                std::cout << "Presumed to read junk data from client." << std::endl;
            }

        }
    }

    return packet;
}

void Server::SendPacketToAddress(PacketBase* packet, Address* address)
{
    /*
  std::cout << "Sending to address: " <<
    (int)(address->GetA()) << "." << (int)(address->GetB()) << "." <<
    (int)(address->GetC()) << "." << (int)(address->GetD()) << ":" <<
    (int)(address->GetPort()) << std::endl;

  std::cout << "Addr: " << (int)address->GetAddress() << std::endl;
  */
    packet->SetConnectionId(0);

    unsigned int data_size;
    char buffer[PacketBase::MAX_BUFFER];

    data_size = packet->Encode(buffer);

    this->socket.Send(*address, buffer, data_size);
}

void Server::TickPacketAcks()
{
    for (unsigned int index = 0; index < this->max_connections; index++)
    {
        ClientConnection* client = this->clients[index];
        if (client)
        {
            client->TickPacketAcks();
        }
    }
}

void Server::TickClientTimeout()
{
    std::list<unsigned int> timeout_list;

    std::list<ClientConnection*>::iterator iter;
    for (iter = this->clients_list.begin(); iter != this->clients_list.end(); ++iter)
    {
        ClientConnection* client = *iter;
        if (client->CheckForTimeout())
        {
            timeout_list.push_back(client->GetConnectionId());
        }
    }

    std::list<unsigned int>::iterator iter2;
    for (iter2 = timeout_list.begin(); iter2 != timeout_list.end(); ++iter2)
    {
        unsigned int id = *iter2;
        this->DisconnectClient(this->clients[id]);

        std::cout << "Client timed out with id: " << id << std::endl;
    }
}

void Server::EstablishDatabaseConnection()
{
    if (!this->database)
    {
        this->database = new Database();
        this->database->Connect();
    }
}

void Server::CloseDatabaseConnection()
{
    if (this->database && this->database->IsConnected())
    {
        this->database->Disconnect();
        delete this->database;
        this->database = nullptr;
    }
}

Database* Server::GetDatabaseConnection() const
{
    return this->database;
}

AccountService& Server::GetAccountService()
{
    return this->accountservice;
}

World* Server::GetWorld()
{
    return this->world;
}

std::list<ClientConnection*> Server::GetClientList() const
{
    return this->clients_list;
}

void Server::ConnectClient(ClientConnection* client)
{
    this->clients[client->GetConnectionId()] = client;
    this->clients_list.push_back(client);
}

void Server::DisconnectClient(ClientConnection* client)
{
    unsigned int con_id = client->GetConnectionId();
    this->clients_list.remove(client);
    this->clients[con_id] = nullptr;
    delete client;
}
