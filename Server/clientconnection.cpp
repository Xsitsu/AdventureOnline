#include "clientconnection.hpp"

#include <iostream>

ClientConnection::ClientConnection(Server* server, Address address, unsigned int connection_id) :
    server(server), client_address(address), connection_id(connection_id), packet_sequence(0), account(NULL)
{

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

    if (packet->GetType() == PacketBase::PACKET_INIT)
    {
        PacketInitResponse* packet = new PacketInitResponse();
        packet->AssignConnectionId(this->connection_id);

        this->SendPacket(packet);
    }
    else if (packet->GetType() == PacketBase::PACKET_DISCONNECT)
    {
        PacketDisconnectResponse* packet = new PacketDisconnectResponse();
        packet->SetNeedsAck(false);
        this->SendPacket(packet);
    }
    else if (packet->GetType() == PacketBase::PACKET_PING)
    {
        PacketPong* packet = new PacketPong();
        packet->SetNeedsAck(false);
        this->SendPacket(packet);
    }
    else if ( packet->GetType() == PacketBase::PACKET_REGISTRATION_REQUEST)
    {
        PacketRegistrationRequest* registration_info = static_cast<PacketRegistrationRequest*>(packet);
        PacketRegistrationResponse * registration_response = new PacketRegistrationResponse();

        Database* database = this->server->GetDatabaseConnection();
        Account* account = database->ReadAccount(registration_info->GetEmail());
        if (account)
        {
            // notify client that account already exists
            std::cout << "Account with email already exists: " << registration_info->GetEmail() << std::endl;
            registration_response->SetResponse(PacketRegistrationResponse::RESPONSE_ACCOUNT_ALREADY_EXISTS);
        }
        else
        {

            try
            {
                database->CreateAccount(registration_info->GetEmail(), registration_info->GetPassword());

                // notify client that account was successfully created
                std::cout << "Account with email was created: " << registration_info->GetEmail() << std::endl;
                registration_response->SetResponse(PacketRegistrationResponse::RESPONSE_ACCOUNT_CREATED);
            }
            catch (DatabaseCreateException &ex)
            {
                // notify client that account creation failed
                std::cout << "Account creation with email failed: " << registration_info->GetEmail() << std::endl;
                registration_response->SetResponse(PacketRegistrationResponse::RESPONSE_ERROR);

            }
        }
        SendPacket(registration_response);
    }
    else if (packet->GetType() == PacketBase::PACKET_LOGIN_REQUEST)
    {
        PacketLoginRequest* login_request = static_cast<PacketLoginRequest*>(packet);
        Database* database = this->server->GetDatabaseConnection();
        Account* account = nullptr;

        bool did_login = false;
        bool was_error = false;

        try
        {
            account = database->ReadAccount(login_request->GetEmail());
            if (account)
            {
                did_login = (account->GetHash() == login_request->GetPassword());
            }
        }
        catch (DatabaseReadException &ex)
        {
            was_error = true;
        }

        PacketLoginResponse* response = new PacketLoginResponse();
        if (did_login)
        {
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_SUCCESS);
            this->account = account;

            std::cout << "Client[" << this->connection_id  << "] logged in as account: " << account->GetEmail() << std::endl;
        }
        else if (was_error)
        {
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_ERROR);
        }
        else
        {
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_FAIL);
        }

        this->SendPacket(response);
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
