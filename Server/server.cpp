#include "server.hpp"

#include <iostream>

Server::Server(unsigned short port) : port(port), connection_id_counter(0)
{}

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

            unsigned long int con_id = this->connection_id_counter++;
            Address clientAddress(sender.GetAddress(), listen_port);
            client = new ClientConnection(this, clientAddress, con_id);
            this->clients[con_id] = client;
        }
        else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
        {
            std::cout << "PacketDisconnect" << std::endl;
            unsigned long int con_id = packet->GetConnectionId();
            client = this->clients[con_id];

            client->ProcessPacket(packet);

            delete packet;
            delete client;

            this->clients[con_id] = NULL;

            return;
        }
        else
        {
            //std::cout << "OtherPacket: " << packet->GetType() << std::endl;

            unsigned long int connection_id = packet->GetConnectionId();
            client = this->clients[connection_id];
        }

        client->ProcessPacket(packet);
        delete packet;
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
