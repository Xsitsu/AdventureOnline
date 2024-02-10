#include "clientstate.hpp"
#include "GameWorld/character.hpp"

ClientStateLoggedIn::ClientStateLoggedIn(ClientConnection* client) : ClientStateBase(client)
{

}

ClientStateLoggedIn::~ClientStateLoggedIn()
{

}

void ClientStateLoggedIn::Enter()
{

}

void ClientStateLoggedIn::Exit()
{

}

bool ClientStateLoggedIn::ProcessPacket(PacketBase* packet)
{
    if (ClientStateBase::ProcessPacket(packet)) return true;

    if (packet->GetType() == PacketBase::PACKET_LOGOUT)
    {
        this->client->DoAccountLogout();

        this->client->ChangeState(new ClientStateNoLogin(this->client));

        return true;
    }
    else if(packet->GetType() == PacketBase::PACKET_CHARACTER_LIST_REQUEST)
    {
        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<uint32_t> character_ids;
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;
            uint32_t id = character->GetCharacterId();
            character_ids.push_back(id);
        }

        PacketCharacterList* packet = new PacketCharacterList();
        packet->SetCharacterList(character_ids);

        this->client->SendPacket(packet);

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_DATA_REQUEST)
    {
        PacketCharacterDataRequest* request = static_cast<PacketCharacterDataRequest*>(packet);

        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;

            if (character->GetCharacterId() == request->GetCharacterId())
            {
                if (request->GetRequestAppearance())
                {
                    PacketCharacterAppearance* packet = new PacketCharacterAppearance();
                    packet->SetCharacterId(character->GetCharacterId());
                    packet->SetName(character->GetName());
                    packet->SetGender(static_cast<uint8_t>(character->GetGender()));
                    packet->SetSkin(static_cast<uint8_t>(character->GetSkin()));
                    packet->SetHair(static_cast<uint8_t>(character->GetHair()));
                    packet->SetHairColor(static_cast<uint8_t>(character->GetHairColor()));

                    this->client->SendPacket(packet);
                }
                if (request->GetRequestPosition())
                {
                    // Maybe eventually.
                }
                if (request->GetRequestStats())
                {
                    // Maybe eventually.
                }
            }
        }
        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_LOGIN)
    {
        PacketCharacterLogin* login_packet = static_cast<PacketCharacterLogin*>(packet);
        unsigned int character_id = login_packet->GetCharacterId();

        std::list<Character*> character_list = this->client->account->GetCharacterList();
        std::list<Character*>::iterator iter;
        for (iter = character_list.begin(); iter != character_list.end(); ++iter)
        {
            Character* character = *iter;
            if (character->GetCharacterId() == character_id)
            {
                this->client->DoCharacterLogin(character);
                this->client->ChangeState(new ClientStatePlaying(this->client));
            }
        }

        return true;
    }
    else if (packet->GetType() == PacketBase::PACKET_CHARACTER_CREATE_REQUEST)
    {
        PacketCharacterCreationRequest * character_create = static_cast<PacketCharacterCreationRequest*>(packet);
        int accID = this->client->account->GetAccountId();
        Character * newCharacter = new Character();
        Database* database = this->client->server->GetDatabaseConnection();
        PacketCharacterCreationResponse * response = new PacketCharacterCreationResponse();

        if((character_create->GetName().size()) < 3
           || (character_create->GetName().size()) > 12
           || client->account->GetCharacterList().size() > 1)
        {
            response->SetResponse(PacketCharacterCreationResponse::RESPONSE_ERROR);
            this->client->SendPacket(response);
        }
        if(database->CharacterExists(character_create->GetName()))
        {
            response->SetResponse(PacketCharacterCreationResponse::RESPONSE_CHARACTER_ALREADY_EXISTS);
            this->client->SendPacket(response);
        }
        else
        {
            newCharacter->SetName(character_create->GetName());
            newCharacter->SetStrength(10);
            newCharacter->SetEndurance(10);
            newCharacter->SetGender(static_cast<Character::Gender>(character_create->GetGender()));
            newCharacter->SetSkin(static_cast<Character::Skin>(character_create->GetSkin()));
            newCharacter->SetMaxHealth(100);
            newCharacter->SetHealth(100);
            newCharacter->SetHair(static_cast<Character::Hair>(character_create->GetHair()));
            newCharacter->SetHairColor(static_cast<Character::HairColor>(character_create->GetHairColor()));
            try
            {
                database->CreateCharacter(accID, newCharacter);
            }
            catch(std::exception& problem)
            {
                database->DeleteCharacter(newCharacter->GetName());
                response->SetResponse(PacketCharacterCreationResponse::RESPONSE_ERROR);
                this->client->SendPacket(response);
                delete newCharacter;
                return true;
            }
            response->SetResponse(PacketCharacterCreationResponse::RESPONSE_CHARACTER_CREATED);
            this->client->SendPacket(response);
            this->client->FetchCharacterList();
        }
        delete newCharacter;
        return true;
    }

    return false;
}
