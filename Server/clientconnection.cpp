#include "clientconnection.hpp"

#include <iostream>

ClientConnection::ClientConnection(Server* server, Address address, unsigned int connection_id) :
connection_id(connection_id), packet_sequence(0), client_address(address), server(server), account(NULL),
state(nullptr)
{
    this->ChangeState(new ClientStateInit(this));
}

ClientConnection::~ClientConnection()
{
    if (this->account)
    {
        this->DoAccountLogout();
    }
}

void ClientConnection::DoAccountLogout()
{
    if (this->account)
    {
        this->server->GetAccountService().UnregisterAccount(this->account->GetAccountId());
        delete this->account;
        this->account = nullptr;
    }
}

void ClientConnection::FetchCharacterList()
{
    if (this->account)
    {
        this->account->ClearCharacterList();

        Database* database = this->server->GetDatabaseConnection();
        std::vector<int> char_id_list = database->ReadPlayerCharacters(this->account->GetEmail());

        std::vector<int>::iterator iter;
        for (iter = char_id_list.begin(); iter != char_id_list.end(); ++iter)
        {
            Character* character = database->ReadCharacterInfo(*iter);
            this->account->AddCharacterToList(character);
        }
    }
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
