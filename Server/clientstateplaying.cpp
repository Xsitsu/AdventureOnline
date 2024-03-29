#include "clientstate.hpp"

ClientStatePlaying::ClientStatePlaying(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStatePlaying::~ClientStatePlaying()
{

}

void ClientStatePlaying::Enter()
{
    unsigned int map_id = 1;
    Vector2 map_pos = Vector2(5, 5);

    World* world = this->client->server->GetWorld();
    if (!world->IsMapLoaded(map_id))
    {
        world->LoadMap(map_id);
    }

    Map* map = world->GetMap(map_id);
    //this->client->DoWarpCharacter(map, map_pos);
    this->client->playing_character->Warp(map, map_pos);
}

void ClientStatePlaying::Exit()
{

}

bool ClientStatePlaying::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_LOGOUT)
    {
        this->client->DoCharacterLogout();
        this->client->DoAccountLogout();

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_DATA_REQUEST)
    {
        PacketCharacterDataRequest* request = static_cast<PacketCharacterDataRequest*>(packet);

        Character* cur_char = this->client->playing_character;
        Map* cur_map = cur_char->GetMap();

        std::list<Character*> character_list = cur_map->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;

            if (character->GetCharacterId() == request->GetCharacterId())
            {
                if (request->GetRequestAppearance())
                {
                    this->client->SendCharacterAppearance(character);
                }
                if (request->GetRequestPosition())
                {
                    this->client->SendCharacterPosition(character);
                }
                if (request->GetRequestStats())
                {
                    this->client->SendCharacterStats(character);
                }
            }
        }
        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_TURN)
    {
        PacketCharacterTurn* turn = static_cast<PacketCharacterTurn*>(packet);

        Character* character = this->client->playing_character;
        if (turn->GetCharacterId() == character->GetCharacterId())
        {
            if (character->CanMove())
            {
                character->Turn(static_cast<Actor::Direction>(turn->GetDirection()));
            }
            else
            {
                this->client->SendCharacterPosition(character);
            }
        }

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_WALK)
    {
        PacketCharacterWalk* walk = static_cast<PacketCharacterWalk*>(packet);

        Character* character = this->client->playing_character;
        //Map* cur_map = character->GetMap();
        if (walk->GetCharacterId() == character->GetCharacterId())
        {
            //Vector2 from_pos = Vector2(walk->GetFromX(), walk->GetFromY());
            Vector2 to_pos = Vector2(walk->GetToX(), walk->GetToY());
            Actor::Direction dir = static_cast<Actor::Direction>(walk->GetDirection());

            try
            {
                if (!character->CanMove()) throw "BREAK";

                character->SetDirection(dir);
                character->Move(to_pos);
            }
            catch(...)
            {
                this->client->SendCharacterPosition(character);
            }
        }

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_ATTACK)
    {
        PacketCharacterAttack *attack = static_cast<PacketCharacterAttack*>(packet);

        Character* character = this->client->playing_character;
        if (attack->GetCharacterId() == character->GetCharacterId())
        {
            try
            {
                if (!character->CanAttack()) throw "BREAK";

                character->Attack();
            }
            catch(...)
            {
                // ToDo: Maybe some other way to let client know of their current state.
                //this->client->SendCharacterPosition(character);
            }
        }

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_LOGOUT)
    {
        this->client->DoCharacterLogout();

        this->client->ChangeState(new ClientStateLoggedIn(this->client));

        return true;
    }

    return false;
}
