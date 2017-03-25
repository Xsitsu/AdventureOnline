#include "clientstate.hpp"

ClientStateNoLogin::ClientStateNoLogin(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStateNoLogin::~ClientStateNoLogin()
{

}

void ClientStateNoLogin::Enter()
{

}

void ClientStateNoLogin::Exit()
{

}

bool ClientStateNoLogin::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_REGISTRATION_REQUEST)
    {
        PacketRegistrationRequest* registration_info = static_cast<PacketRegistrationRequest*>(packet);
        PacketRegistrationResponse * registration_response = new PacketRegistrationResponse();

        Database* database = this->client->server->GetDatabaseConnection();
        Account* account = database->ReadAccount(registration_info->GetEmail());
        if (account)
        {
            // notify client that account already exists
            std::cout << "Account with email already exists: " << registration_info->GetEmail() << std::endl;
            registration_response->SetResponse(PacketRegistrationResponse::RESPONSE_ACCOUNT_ALREADY_EXISTS);

            delete account;
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
        this->client->SendPacket(registration_response);
        std::cout << "Sent response package with code: " << registration_response->GetResponse() << std::endl;

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_LOGIN_REQUEST)
    {
        PacketLoginRequest* login_request = static_cast<PacketLoginRequest*>(packet);
        Database* database = this->client->server->GetDatabaseConnection();
        Account* account = nullptr;

        bool can_login = false;
        bool did_login = false;
        bool was_error = false;

        try
        {
            account = database->ReadAccount(login_request->GetEmail());
            if (account)
            {
                can_login = (account->GetHash() == login_request->GetPassword());
                if (can_login)
                {
                    AccountService& service = this->client->server->GetAccountService();
                    did_login = !service.IsAccountRegistered(account->GetAccountId());
                }
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
            this->client->account = account;

            AccountService& service = this->client->server->GetAccountService();
            service.RegisterAccount(account->GetAccountId(), account);

            std::cout << "Client[" << this->client->connection_id  << "] logged in as account: " << account->GetEmail() << std::endl;
        }
        else if (can_login)
        {
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_ALREADY_LOGGED_IN);
            std::cout << "Client[" << this->client->connection_id  << "] tried to log in as account [" << account->GetEmail() << "]"
            << " but another account is already logged in!" << std::endl;
        }
        else if (was_error)
        {
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_ERROR);
        }
        else
        {
            delete account;
            response->SetResponse(PacketLoginResponse::LOGINRESPONSE_FAIL);
        }

        this->client->SendPacket(response);

        if (did_login)
        {
            this->client->ChangeState(new ClientStateLoggedIn(this->client));
        }

        return true;
    }

    return false;
}
