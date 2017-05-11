#include "clientconnection.hpp"

#include <iostream>

ClientConnection::ClientConnection(Server* server, Address address, unsigned int connection_id) :
connection_id(connection_id), packet_sequence(0), client_address(address), server(server), account(NULL),
playing_character(nullptr), state(nullptr)
{
    this->ChangeState(new ClientStateInit(this));
    this->character_manager = new ActorManagerCharacter(this);
}

ClientConnection::~ClientConnection()
{
    if (this->playing_character)
    {
        this->DoCharacterLogout();
    }
    if (this->account)
    {
        this->DoAccountLogout();
    }

    delete this->character_manager;
}

Server* ClientConnection::GetServer() const
{
    return this->server;
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
            character->SetCharacterId(*iter);
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
        std::cout << "In State: " << this->state->GetName() << std::endl;
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

Character* ClientConnection::GetPlayingCharacter()
{
    return this->playing_character;
}

void ClientConnection::DoCharacterLogin(Character *login_char)
{
    this->playing_character = login_char;
    login_char->SetActorManager(this->character_manager);
}

void ClientConnection::DoCharacterLogout()
{
    this->playing_character->SetActorManager(nullptr);

    Map* map = this->playing_character->GetMap();
    if (map)
    {
        World* world = this->server->GetWorld();

        unsigned int map_id = map->GetMapId();
        world->UnregisterClientInMap(this, map_id);


        /*
        std::list<ClientConnection*> clients = world->GetClientsInMap(map_id);
        std::list<ClientConnection*>::iterator iter;
        for (iter = clients.begin(); iter != clients.end(); ++iter)
        {
            ClientConnection* client = *iter;
            client->SendCharacterMapLeave(this->playing_character);
        }
        */

        this->playing_character->ExitMap(map);
    }
}
void ClientConnection::DoWarpCharacter(Map* map, Vector2 map_pos)
{
    World* world = this->server->GetWorld();

    Map* last_map = this->playing_character->GetMap();
    if (last_map)
    {
        unsigned int map_id = last_map->GetMapId();
        world->UnregisterClientInMap(this, map_id);

        std::list<ClientConnection*> clients = world->GetClientsInMap(map_id);
        std::list<ClientConnection*>::iterator iter;
        for (iter = clients.begin(); iter != clients.end(); ++iter)
        {
            ClientConnection* client = *iter;
            client->SendCharacterMapLeave(this->playing_character);
        }

    }

    this->playing_character->Warp(map, map_pos);

    unsigned int map_id = map->GetMapId();

    std::list<ClientConnection*> clients = world->GetClientsInMap(map_id);
    std::list<ClientConnection*>::iterator iter;
    for (iter = clients.begin(); iter != clients.end(); ++iter)
    {
        ClientConnection* client = *iter;
        client->SendCharacterMapEnter(this->playing_character);
    }

    world->RegisterClientInMap(this, map_id);

    PacketCharacterPosition* packet = new PacketCharacterPosition();
    packet->SetCharacterId(this->playing_character->GetCharacterId());
    packet->SetMapId(map->GetMapId());
    packet->SetPositionX(map_pos.x);
    packet->SetPositionY(map_pos.y);
    packet->SetDirection(static_cast<uint8_t>(this->playing_character->GetDirection()));

    this->SendPacket(packet);

    std::list<Character*> character_list = map->GetCharacterList();
    std::list<Character*>::iterator iter2;
    for (iter2 = character_list.begin(); iter2 != character_list.end(); ++iter2)
    {
        Character* other = *iter2;
        if (other != this->playing_character)
        {
            this->SendCharacterMapEnter(other);
        }
    }
}

void ClientConnection::SendCharacterAppearance(Character* character)
{
    PacketCharacterAppearance* packet = new PacketCharacterAppearance();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetName(character->GetName());
    packet->SetGender(static_cast<uint8_t>(character->GetGender()));
    packet->SetSkin(static_cast<uint8_t>(character->GetSkin()));
    packet->SetHair(static_cast<uint8_t>(character->GetHair()));
    packet->SetHairColor(static_cast<uint8_t>(character->GetHairColor()));

    this->SendPacket(packet);
}

void ClientConnection::SendCharacterPosition(Character* character)
{
    PacketCharacterPosition* packet = new PacketCharacterPosition();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetMapId(character->GetMap()->GetMapId());
    packet->SetPositionX(character->GetPosition().x);
    packet->SetPositionY(character->GetPosition().y);
    packet->SetDirection(character->GetDirection());

    this->SendPacket(packet);
}

void ClientConnection::SendCharacterMapEnter(Character* character)
{
    PacketCharacterMapEnter* packet = new PacketCharacterMapEnter();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetMapId(this->playing_character->GetMap()->GetMapId());

    this->SendPacket(packet);
}

void ClientConnection::SendCharacterMapLeave(Character* character)
{
    PacketCharacterMapLeave* packet = new PacketCharacterMapLeave();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetMapId(this->playing_character->GetMap()->GetMapId());

    this->SendPacket(packet);
}

void ClientConnection::SendCharacterTurn(Character* character)
{
    PacketCharacterTurn* packet = new PacketCharacterTurn();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetDirection(character->GetDirection());

    this->SendPacket(packet);
}

void ClientConnection::SendCharacterWalk(Character* character)
{
    Actor::Direction dir = character->GetDirection();
    Vector2 cur_pos = character->GetPosition();
    Vector2 prev_pos = cur_pos;
    if (dir == Actor::DIR_DOWN)
    {
        prev_pos.y -= 1;
    }
    else if (dir == Actor::DIR_LEFT)
    {
        prev_pos.x += 1;
    }
    else if (dir == Actor::DIR_UP)
    {
        prev_pos.y += 1;
    }
    else if (dir == Actor::DIR_RIGHT)
    {
        prev_pos.x -= 1;
    }

    PacketCharacterWalk* packet = new PacketCharacterWalk();
    packet->SetCharacterId(character->GetCharacterId());
    packet->SetFromX(prev_pos.x);
    packet->SetFromY(prev_pos.y);
    packet->SetToX(cur_pos.x);
    packet->SetToY(cur_pos.y);
    packet->SetDirection(character->GetDirection());

    this->SendPacket(packet);
}
