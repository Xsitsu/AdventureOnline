#include "server.hpp"

#include <iostream>

Server::Server(unsigned short port, unsigned int max_connections) : port(port), connection_id_counter(0),
max_connections(max_connections)
{
    clients = new ClientConnection*[max_connections];
}

Server::~Server()
{
    delete[] clients;
}

unsigned int Server::FindOpenConnectionId()
{
    unsigned int start = this->connection_id_counter;
    unsigned int id = start;
    unsigned int max = this->max_connections;

    while (this->clients[start] != NULL)
    {
        std::cout << "Scanning: " << id << "/" << max << std::endl;

        id++;
        if (id >= max)
        {
            id -= max;
        }

        if (id == start)
        {
            std::cout << "No open connections!" << std::endl;
            throw "fail";
        }
    }

    this->connection_id_counter = id + 1;

    if (this->connection_id_counter >= max)
    {
        this->connection_id_counter -= max;
    }

    std::cout << "Returning: " << id << std::endl;
    return id;
}

bool Server::Init()
{
    if(this->socket.IsOpen()) return false;

    this->socket.Open(this->port, true);
    if (!this->socket.IsOpen()) return false;

    return true;
}

void Server::Tick()
{
    Address sender;
    PacketBase* packet = this->ReceivePacket(sender);
    if (packet)
    {
        std::cout << "Got a packet. [" << packet->GetSequence() << "]" << std::endl;

        ClientConnection* client = NULL;
        if (packet->GetType() == PacketBase::PACKET_INIT)
        {
            std::cout << "PacketInit" << std::endl;
            unsigned short listen_port = ((PacketInit*)packet)->GetListenPort();

            unsigned int con_id;
            try
            {
                con_id = this->FindOpenConnectionId();
            }
            catch (...)
            {
                std::cout << "Refusing connection!" << std::endl;
                delete packet;
                return;
            }

            Address clientAddress(sender.GetAddress(), listen_port);
            client = new ClientConnection(this, clientAddress, con_id);
            this->clients[con_id] = client;
        }
        else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
        {
            std::cout << "PacketDisconnect" << std::endl;
            unsigned long int con_id = packet->GetConnectionId();
            client = this->clients[con_id];

            if (!client) return;

            client->ProcessPacket(packet);

            delete packet;
            delete client;

            this->clients[con_id] = NULL;

            return;
        }
        else
        {
            //std::cout << "OtherPacket: " << packet->GetType() << std::endl;

            unsigned int connection_id = packet->GetConnectionId();
            client = this->clients[connection_id];
        }

        if (client)
        {
            client->ProcessPacket(packet);
        }
        else
        {
            std::cout << "Client didn't exist with expected id: " << packet->GetConnectionId() << std::endl;
        }

        delete packet;
    }

    this->TickPacketAcks();
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
  std::cout << "Sending to address: " <<
    (int)(address->GetA()) << "." << (int)(address->GetB()) << "." <<
    (int)(address->GetC()) << "." << (int)(address->GetD()) << ":" <<
    (int)(address->GetPort()) << std::endl;

  std::cout << "Addr: " << (int)address->GetAddress() << std::endl;

  packet->SetConnectionId(0);

    char buffer[PacketBase::MAX_BUFFER];
    unsigned int data_size = packet->Encode(buffer);

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
