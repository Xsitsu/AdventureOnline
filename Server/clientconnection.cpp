#include "clientconnection.hpp"

#include <iostream>
#include <vector>
using std::vector;

ClientConnection::ClientConnection(Server* server, Address address, unsigned int connection_id) :
connection_id(connection_id), packet_sequence(0), client_address(address), server(server), account(NULL),
state(nullptr)
{
    this->ChangeState(new ClientStateInit(this));
}

void ClientConnection::SendPacket(PacketBase* packet)
{
    packet->SetSequence(this->packet_sequence++);
    packet->SetAck(this->ack_list.GetPacketAck());
    packet->SetAckBitfield(this->ack_list.GetPacketAckBitfield());

    this->server->SendPacketToAddress(packet, &(this->client_address));

    if (packet->GetNeedsAck())
    {
        this->ack_list.RegisterPacket(packet);
    }
    else
    {
        delete packet;
    }
}

void ClientConnection::ProcessPacket(PacketBase* packet)
{
    this->ack_list.UpdatePacketAck(packet->GetSequence());
    this->ack_list.ConfirmPacketAcks(packet->GetAck(), packet->GetAckBitfield());

    bool was_processed = this->state->ProcessPacket(packet);
    if (was_processed)
    {
        // stuff
    }
    else
    {
        std::cout << "Dropping packet [id:" << packet->GetType() << "] [sequence:" << packet->GetSequence() << "]" << std::endl;
    }
    else if(packet->GetType() == PacketBase::PACKET_DATA_REQUEST)
    {
        Database * database = this->server->GetDatabaseConnection();
        PacketCharacter * returnCharacter = new PacketCharacter();
        Character PC;
        vector<int> characters = database->ReadePlayerCharacters(account->GetEmail());
        vector<int>::iterator it = characters.begin();
        while(it < characters.end())
        {
            returnCharacter->SetCharacters(database->ReadCharacterInfo( *it++) );
            this->SendPacket(returnCharacter);
            returnCharacter = new PacketCharacter();
        }

    }
}

void ClientConnection::TickPacketAcks()
{
    std::list<PacketBase*> resend_list = this->ack_list.TickPacketAcks();
    while (!resend_list.empty())
    {
        this->SendPacket(resend_list.front());
        resend_list.pop_front();
    }
}

bool ClientConnection::CheckForTimeout()
{
    return (std::time(NULL) - this->last_communication > this->CONNECTION_TIMEOUT);
}

void ClientConnection::UpdateLastCommunicationTime()
{
    this->last_communication = std::time(NULL);
}

void ClientConnection::ChangeState(ClientStateBase* state)
{
    if (this->state)
    {
        this->state->Exit();
        delete this->state;
    }

    this->state = state;

    this->state->Enter();
}
