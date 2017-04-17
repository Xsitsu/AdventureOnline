#include "packet.hpp"

#include <iostream>

char first = 'A';   //Adventure
char second = 'O';  //Online
char third = 'P';   //Packet
char fourth = 'F';  //Format

unsigned int data = (first << 24) | (second < 16) | (third << 8) | fourth;

const unsigned int PacketBase::MAX_BUFFER = 1024;
const unsigned int PacketBase::PACKET_PREFIX = data;

PacketBase::PacketBase() : type(PacketBase::PACKET_UNKNOWN)
{

}

PacketBase::PacketBase(PacketBase::PacketType type) : needs_ack(true), type(type)
{

}

PacketBase::PacketBase(PacketBase::PacketType type, bool needs_ack) : needs_ack(needs_ack), type(type)
{

}

unsigned int PacketBase::Encode(char* buffer)
{
    PacketReader reader;

    this->buffer_pos = 0;
    reader.WriteInt(buffer, this->buffer_pos, PacketBase::PACKET_PREFIX);
    reader.WritePacketType(buffer, this->buffer_pos, this->type);
    reader.WriteInt(buffer, this->buffer_pos, this->connection_id);
    reader.WriteInt(buffer, this->buffer_pos, this->sequence);
    reader.WriteInt(buffer, this->buffer_pos, this->ack);
    reader.WriteInt(buffer, this->buffer_pos, this->ack_bitfield);

    return this->buffer_pos;
}

void PacketBase::Decode(char* buffer)
{
    PacketReader reader;

    this->buffer_pos = 0;
    reader.ReadInt(buffer, this->buffer_pos);
    reader.ReadPacketType(buffer, this->buffer_pos);
    this->connection_id = reader.ReadInt(buffer, this->buffer_pos);
    this->sequence = reader.ReadInt(buffer, this->buffer_pos);
    this->ack = reader.ReadInt(buffer, this->buffer_pos);
    this->ack_bitfield = reader.ReadInt(buffer, this->buffer_pos);
}

PacketBase* PacketReader::ReadPacket(char* buffer, int bytes_read)
{
    unsigned int pos = 0;
    unsigned int prefix = this->ReadInt(buffer,  pos);
    if (prefix != PacketBase::PACKET_PREFIX)
    {
        return NULL;
    }

    PacketBase::PacketType type = this->ReadPacketType(buffer, pos);
    PacketBase* packet = NULL;

    switch (type)
    {
    case PacketBase::PACKET_INIT:
        packet = new PacketInit();
        break;
    case PacketBase::PACKET_INIT_RESPONSE:
        packet = new PacketInitResponse();
        break;
    case PacketBase::PACKET_DISCONNECT:
        packet = new PacketDisconnect();
        break;
    case PacketBase::PACKET_DISCONNECT_RESPONSE:
        packet = new PacketDisconnectResponse();
        break;
    case PacketBase::PACKET_PING:
        packet = new PacketPing();
        break;
    case PacketBase::PACKET_PONG:
        packet = new PacketPong();
        break;
    case PacketBase::PACKET_REGISTRATION_REQUEST:
        packet = new PacketRegistrationRequest();
        break;
    case PacketBase::PACKET_REGISTRATION_RESPONSE:
        packet = new PacketRegistrationResponse();
        break;
    case PacketBase::PACKET_LOGIN_REQUEST:
        packet = new PacketLoginRequest();
        break;
    case PacketBase::PACKET_LOGIN_RESPONSE:
        packet = new PacketLoginResponse();
        break;
    case PacketBase::PACKET_LOGOUT:
        packet = new PacketLogout();
        break;
    case PacketBase::PACKET_CHARACTER_LIST_REQUEST:
        packet = new PacketCharacterListRequest();
        break;
    case PacketBase::PACKET_CHARACTER_LIST:
        packet = new PacketCharacterList();
        break;
    case PacketBase::PACKET_CHARACTER_DATA_REQUEST:
        packet = new PacketCharacterDataRequest();
        break;
    case PacketBase::PACKET_CHARACTER_LOGIN:
        packet = new PacketCharacterLogin();
        break;
    case PacketBase::PACKET_CHARACTER_LOGOUT:
        packet = new PacketCharacterLogout();
        break;
    case PacketBase::PACKET_CHARACTER_APPEARANCE:
        packet = new PacketCharacterAppearance();
        break;
    case PacketBase::PACKET_CHARACTER_POSITION:
        packet = new PacketCharacterPosition();
        break;
    case PacketBase::PACKET_CHARACTER_MAP_ENTER:
        packet = new PacketCharacterMapEnter();
        break;
    case PacketBase::PACKET_CHARACTER_MAP_LEAVE:
        packet = new PacketCharacterMapLeave();
        break;
    case PacketBase::PACKET_CHARACTER_TURN:
        packet = new PacketCharacterTurn();
        break;
    case PacketBase::PACKET_CHARACTER_WALK:
        packet = new PacketCharacterWalk();
        break;
    case PacketBase::PACKET_CHARACTER_CREATE_REQUEST:
        packet = new PacketCharacterCreationRequest();
        break;
    case PacketBase::PACKET_CHARACTER_CREATE_RESPONSE:
        packet = new PacketCharacterCreationResponse();
        break;
    default:
        //std::cout << "bad type: " << (unsigned int) type << std::endl;s
        break;
    }

    if (packet)
    {
        packet->Decode(buffer);
    }

    return packet;
}

void PacketReader::WritePacketType(char* buffer, unsigned int& pos, PacketBase::PacketType type)
{
    char* buf_pos = buffer + pos;
    *((PacketBase::PacketType*)buf_pos) = type;
    pos+=sizeof(PacketBase::PacketType);
}

PacketBase::PacketType PacketReader::ReadPacketType(char* buffer, unsigned int& pos)
{
    char* buf_pos = buffer + pos;
    PacketBase::PacketType val = *((PacketBase::PacketType*)buf_pos);
    pos+=sizeof(PacketBase::PacketType);
    return val;
}

void PacketReader::WriteInt(char* buffer, unsigned int& pos, uint32_t value)
{
    char* buf_pos = buffer + pos;
    *((uint32_t*)buf_pos) = htonl(value);
    pos+=sizeof(uint32_t);
}

uint32_t PacketReader::ReadInt(char* buffer, unsigned int& pos)
{
    char* buf_pos = buffer + pos;
    uint32_t val = *((uint32_t*)buf_pos);
    pos+=sizeof(uint32_t);
    return ntohl(val);
}

void PacketReader::WriteLongInt(char* buffer, unsigned int& pos, uint64_t value)
{
    char* buf_pos = buffer + pos;

     uint64_t write_val = ((uint64_t)(htonl((uint32_t)(value >> 32))) << 32);
     write_val = write_val | htonl((uint32_t)value);

     *((uint64_t*)buf_pos) = write_val;
    pos+=sizeof(uint64_t);
}

uint64_t PacketReader::ReadLongInt(char* buffer, unsigned int& pos)
{
    char* buf_pos = buffer + pos;
    uint64_t val = *((uint64_t*)buf_pos);
    pos+=sizeof(uint64_t);

    uint64_t ret_val = ((uint64_t)(ntohl((uint32_t)(val >> 32))) << 32);
    ret_val = ret_val | ntohl((uint32_t)val);

    return ret_val;
}

void PacketReader::WriteShort(char* buffer, unsigned int& pos, uint16_t value)
{
    char* buf_pos = buffer + pos;
    *((uint16_t*)buf_pos) = htons(value);
    pos+=sizeof(uint16_t);
}

uint16_t PacketReader::ReadShort(char* buffer, unsigned int& pos)
{
    char* buf_pos = buffer + pos;
    uint16_t val = *((uint16_t*)buf_pos);
    pos+=sizeof(uint16_t);
    return ntohs(val);
}


void PacketReader::WriteByte(char* buffer, unsigned int& pos, uint8_t value)
{
    char* buf_pos = buffer + pos;
    *((uint8_t*)buf_pos) = value;
    pos+=sizeof(uint8_t);
}

uint8_t PacketReader::ReadByte(char* buffer, unsigned int& pos)
{
    char* buf_pos = buffer + pos;
    uint8_t val = *((uint8_t*)buf_pos);
    pos+=sizeof(uint8_t);
    return val;
}

PacketInit::PacketInit() : PacketBase(PacketBase::PACKET_INIT)
{}

unsigned int PacketInit::Encode(char* buffer)
{
    PacketBase::Encode(buffer);
    PacketReader reader;
    reader.WriteShort(buffer, this->buffer_pos, this->listen_port);

    return this->buffer_pos;
}

void PacketInit::Decode(char* buffer)
{
    PacketBase::Decode(buffer);
    PacketReader reader;
    this->listen_port = reader.ReadShort(buffer, this->buffer_pos);
}

PacketInitResponse::PacketInitResponse() : PacketBase(PacketBase::PACKET_INIT_RESPONSE),
connection_accepted(true), assigned_connection_id(0)
{}

unsigned int PacketInitResponse::Encode(char* buffer)
{
    PacketBase::Encode(buffer);
    PacketReader reader;
    reader.WriteByte(buffer, this->buffer_pos, this->connection_accepted);
    reader.WriteLongInt(buffer, this->buffer_pos, this->assigned_connection_id);

    return this->buffer_pos;
}

void PacketInitResponse::Decode(char* buffer)
{
    PacketBase::Decode(buffer);
    PacketReader reader;
    this->connection_accepted = reader.ReadByte(buffer, this-> buffer_pos);
    this->assigned_connection_id = reader.ReadLongInt(buffer, this->buffer_pos);
}

PacketDisconnect::PacketDisconnect() : PacketBase(PacketBase::PACKET_DISCONNECT)
{}

PacketDisconnectResponse::PacketDisconnectResponse() : PacketBase(PacketBase::PACKET_DISCONNECT_RESPONSE, false)
{}

PacketPing::PacketPing() : PacketBase(PacketBase::PACKET_PING)
{}

PacketPong::PacketPong() : PacketBase(PacketBase::PACKET_PONG)
{}

unsigned int PacketRegistrationRequest::Encode(char* buffer)
{
    const char * email = p_email.c_str();
    const char * password = p_password.c_str();
    PacketReader reader;
    //this->buffer_pos = 0;

    PacketBase::Encode(buffer);
    reader.WriteByte(buffer, this->buffer_pos, this->email_length);
    reader.WriteByte(buffer, this->buffer_pos, this->password_length);


    for (uint8_t c = 0; c < email_length ; c++)
    {
        reader.WriteByte(buffer, this->buffer_pos, email[c]);
    }

    for (uint8_t c = 0; c < password_length ; c++)
    {
        reader.WriteByte(buffer, this->buffer_pos, password[c]);
    }

    return this->buffer_pos;
}

void PacketRegistrationRequest::Decode(char* buffer)
{
    PacketReader reader;
    char buff;
    PacketBase::Decode(buffer);
    uint8_t email_length = reader.ReadByte(buffer, buffer_pos);
    uint8_t password_length = reader.ReadByte(buffer, buffer_pos);

    char * email = new char[email_length+1];
    char * pass = new char [password_length+1];

    for(int i = 0; i < email_length; i++)
    {
        buff = reader.ReadByte(buffer, buffer_pos);
        email[i] = buff;
    }
    email[email_length] = 0;

    for(int i = 0; i < password_length; i++)
    {
        buff = reader.ReadByte(buffer, buffer_pos);
        pass[i] = buff;
    }
    pass[password_length] = 0;

    this->SetEmail(email);
    this->SetPassword(pass);

    delete[] email;
    delete[] pass;
}

std::string PacketRegistrationRequest::GetEmail()
{
    return p_email;
}

std::string PacketRegistrationRequest::GetPassword()
{
    return p_password;
}

void PacketRegistrationRequest::SetEmail(std::string email)
{
    p_email = email;
    email_length = p_email.size();
}

void PacketRegistrationRequest::SetPassword(std::string password)
{
    p_password = password;
    password_length = p_password.size();
}

PacketRegistrationRequest::PacketRegistrationRequest(): PacketBase(PacketBase::PACKET_REGISTRATION_REQUEST), p_email(""), p_password(""), email_length(0), password_length(0){}

PacketRegistrationResponse::PacketRegistrationResponse(): PacketBase(PacketBase::PACKET_REGISTRATION_RESPONSE) {}

PacketRegistrationResponse::Response PacketRegistrationResponse::GetResponse() { return returnCode; }
void PacketRegistrationResponse::SetResponse(PacketRegistrationResponse::Response val) { returnCode = val; }

unsigned int PacketRegistrationResponse::Encode(char* buffer)
{
    PacketReader reader;
    PacketBase::Encode(buffer);
    reader.WriteByte(buffer, buffer_pos, static_cast<uint8_t>(returnCode));
    return buffer_pos;
}

void PacketRegistrationResponse::Decode(char* buffer)
{
    PacketReader reader;
    PacketBase::Decode(buffer);
    returnCode = static_cast<Response>(reader.ReadByte(buffer, buffer_pos));
}



PacketLoginRequest::PacketLoginRequest() : PacketBase(PacketBase::PACKET_LOGIN_REQUEST)
{

}

void PacketLoginRequest::SetEmail(std::string email)
{
    this->email = email;
    this->email_length = email.size();
}

void PacketLoginRequest::SetPassword(std::string password)
{
    this->password = password;
    this->password_length = password.size();
}

unsigned int PacketLoginRequest::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;

    const char* email = this->email.c_str();
    const char* password = this->password.c_str();

    reader.WriteByte(buffer, this->buffer_pos, this->email_length);
    reader.WriteByte(buffer, this->buffer_pos, this->password_length);

    for (uint8_t c = 0; c < this->email_length ; c++)
    {
        reader.WriteByte(buffer, this->buffer_pos, email[c]);
    }

    for (uint8_t c = 0; c < this->password_length ; c++)
    {
        reader.WriteByte(buffer, this->buffer_pos, password[c]);
    }

    return this->buffer_pos;
}

void PacketLoginRequest::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;

    uint8_t email_length = reader.ReadByte(buffer, buffer_pos);
    uint8_t password_length = reader.ReadByte(buffer, buffer_pos);

    char* email = new char[email_length+1];
    char* pass = new char [password_length+1];

    for(int i = 0; i < email_length; i++)
    {
        email[i] = static_cast<char>(reader.ReadByte(buffer, this->buffer_pos));
    }
    email[email_length] = 0;

    for(int i = 0; i < password_length; i++)
    {
        pass[i] = static_cast<char>(reader.ReadByte(buffer, this->buffer_pos));
    }
    pass[password_length] = 0;

    this->SetEmail(email);
    this->SetPassword(pass);

    delete[] email;
    delete[] pass;
}




PacketLoginResponse::PacketLoginResponse() : PacketBase(PacketBase::PACKET_LOGIN_RESPONSE), response(PacketLoginResponse::LOGINRESPONSE_FAIL)
{

}

unsigned int PacketLoginResponse::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteByte(buffer, this->buffer_pos, static_cast<uint8_t>(this->response));

    return this->buffer_pos;
}

void PacketLoginResponse::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->response = static_cast<PacketLoginResponse::LoginResponse>(reader.ReadByte(buffer, this->buffer_pos));
}

PacketLogout::PacketLogout() : PacketBase(PacketBase::PACKET_LOGOUT)
{}

PacketCharacterListRequest::PacketCharacterListRequest(): PacketBase(PacketBase::PACKET_CHARACTER_LIST_REQUEST)
{}

PacketCharacterList::PacketCharacterList(): PacketBase(PacketBase::PACKET_CHARACTER_LIST)
{}

unsigned int PacketCharacterList::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    uint8_t list_size = this->character_ids.size();

    PacketReader reader;
    reader.WriteByte(buffer, this->buffer_pos, list_size);

    std::list<uint32_t>::iterator iter;
    for (iter = this->character_ids.begin(); iter != this->character_ids.end(); ++iter)
    {
        uint32_t character_id = *iter;
        reader.WriteInt(buffer,  this->buffer_pos, character_id);
    }

    return this->buffer_pos;
}

void PacketCharacterList::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    uint8_t list_size = reader.ReadByte(buffer, this->buffer_pos);

    for (uint8_t i = 0; i < list_size; i++)
    {
        uint32_t character_id = reader.ReadInt(buffer, this->buffer_pos);
        this->character_ids.push_back(character_id);
    }
}

std::list<uint32_t> PacketCharacterList::GetCharacterList() const
{
    return this->character_ids;
}

void PacketCharacterList::SetCharacterList(std::list<uint32_t> character_ids)
{
    this->character_ids = character_ids;
}


PacketCharacterDataRequest::PacketCharacterDataRequest(): PacketBase(PacketBase::PACKET_CHARACTER_DATA_REQUEST),
request_appearance(false), request_position(false), request_stats(false)
{}

unsigned int PacketCharacterDataRequest::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    uint8_t bitfield = 0;
    if (this->request_appearance)
    {
        bitfield = bitfield | this->BIT_APPEARANCE;
    }
    if (this->request_position)
    {
        bitfield = bitfield | this->BIT_POSITION;
    }
    if (this->request_stats)
    {
        bitfield = bitfield | this->BIT_STATS;
    }

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteByte(buffer, this->buffer_pos, bitfield);

    return this->buffer_pos;
}

void PacketCharacterDataRequest::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    uint8_t bitfield = reader.ReadByte(buffer, this->buffer_pos);

    this->request_appearance = ((bitfield & this->BIT_APPEARANCE) == this->BIT_APPEARANCE);
    this->request_position = ((bitfield & this->BIT_POSITION) == this->BIT_POSITION);
    this->request_stats = ((bitfield & this->BIT_STATS) == this->BIT_STATS);
}

uint32_t PacketCharacterDataRequest::GetCharacterId() const
{
    return this->character_id;
}

void PacketCharacterDataRequest::SetCharacterId(uint32_t character_id)
{
    this->character_id = character_id;
}

bool PacketCharacterDataRequest::GetRequestAppearance() const
{
    return this->request_appearance;
}

bool PacketCharacterDataRequest::GetRequestPosition() const
{
    return this->request_position;
}

bool PacketCharacterDataRequest::GetRequestStats() const
{
    return this->request_stats;
}

void PacketCharacterDataRequest::SetRequestAppearance(bool val)
{
    this->request_appearance = val;
}

void PacketCharacterDataRequest::SetRequestPosition(bool val)
{
    this->request_position = val;
}

void PacketCharacterDataRequest::SetRequestStats(bool val)
{
    this->request_stats = val;
}

PacketCharacterLogin::PacketCharacterLogin(): PacketBase(PacketBase::PACKET_CHARACTER_LOGIN)
{}

unsigned int PacketCharacterLogin::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);

    return this->buffer_pos;
}

void PacketCharacterLogin::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
}

uint32_t PacketCharacterLogin::GetCharacterId() const
{
    return this->character_id;
}

void PacketCharacterLogin::SetCharacterId(uint32_t character_id)
{
    this->character_id = character_id;
}


PacketCharacterLogout::PacketCharacterLogout() : PacketBase(PacketBase::PACKET_CHARACTER_LOGOUT)
{}

unsigned int PacketCharacterLogout::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    return this->buffer_pos;
}

void PacketCharacterLogout::Decode(char* buffer)
{
    PacketBase::Decode(buffer);
}

PacketCharacterAppearance::PacketCharacterAppearance() : PacketBase(PacketBase::PACKET_CHARACTER_APPEARANCE)
{}

unsigned int PacketCharacterAppearance::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;

    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteByte(buffer, this->buffer_pos, this->gender);
    reader.WriteByte(buffer, this->buffer_pos, this->skin);

    uint8_t name_length = this->name.length();
    reader.WriteByte(buffer, this->buffer_pos, name_length);

    const char* cstr = this->name.c_str();

    for (uint8_t i = 0; i < name_length; i++)
    {
        uint8_t byte = cstr[i];
        reader.WriteByte(buffer, this->buffer_pos, byte);
    }

    return this->buffer_pos;
}

void PacketCharacterAppearance::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;

    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->gender = reader.ReadByte(buffer, this->buffer_pos);
    this->skin = reader.ReadByte(buffer, this->buffer_pos);

    uint8_t name_length = reader.ReadByte(buffer, this->buffer_pos);

    for (uint8_t i = 0; i < name_length; i++)
    {
        char c = reader.ReadByte(buffer, this->buffer_pos);
        this->name += c;
    }
}

uint32_t PacketCharacterAppearance::GetCharacterId() const
{
    return this->character_id;
}

std::string PacketCharacterAppearance::GetName() const
{
    return this->name;
}

uint8_t PacketCharacterAppearance::GetGender() const
{
    return this->gender;
}

uint8_t PacketCharacterAppearance::GetSkin() const
{
    return this->skin;
}

void PacketCharacterAppearance::SetCharacterId(uint32_t character_id)
{
    this->character_id = character_id;
}

void PacketCharacterAppearance::SetName(std::string name)
{
    this->name = name;
}

void PacketCharacterAppearance::SetGender(uint8_t gender)
{
    this->gender = gender;
}

void PacketCharacterAppearance::SetSkin(uint8_t skin)
{
    this->skin = skin;
}

PacketCharacterPosition::PacketCharacterPosition() : PacketBase(PacketBase::PACKET_CHARACTER_POSITION)
{}

unsigned int PacketCharacterPosition::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;

    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteShort(buffer, this->buffer_pos, this->map_id);
    reader.WriteShort(buffer, this->buffer_pos, this->position_x);
    reader.WriteShort(buffer, this->buffer_pos, this->position_y);
    reader.WriteByte(buffer, this->buffer_pos, this->direction);

    return this->buffer_pos;
}

void PacketCharacterPosition::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;

    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->map_id = reader.ReadShort(buffer, this->buffer_pos);
    this->position_x = reader.ReadShort(buffer, this->buffer_pos);
    this->position_y = reader.ReadShort(buffer, this->buffer_pos);
    this->direction = reader.ReadByte(buffer, this->buffer_pos);
}

uint32_t PacketCharacterPosition::GetCharacterId() const
{
    return this->character_id;
}

uint16_t PacketCharacterPosition::GetMapId() const
{
    return this->map_id;
}

uint16_t PacketCharacterPosition::GetPositionX() const
{
    return this->position_x;
}

uint16_t PacketCharacterPosition::GetPositionY() const
{
    return this->position_y;
}

uint8_t PacketCharacterPosition::GetDirection() const
{
    return this->direction;
}

void PacketCharacterPosition::SetCharacterId(uint32_t id)
{
    this->character_id = id;
}

void PacketCharacterPosition::SetMapId(uint16_t id)
{
    this->map_id = id;
}

void PacketCharacterPosition::SetPositionX(uint16_t pos_x)
{
    this->position_x = pos_x;
}

void PacketCharacterPosition::SetPositionY(uint16_t pos_y)
{
    this->position_y = pos_y;
}

void PacketCharacterPosition::SetDirection(uint8_t direction)
{
    this->direction = direction;
}

PacketCharacterMapEnter::PacketCharacterMapEnter() : PacketBase(PacketBase::PACKET_CHARACTER_MAP_ENTER)
{}

unsigned int PacketCharacterMapEnter::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteShort(buffer, this->buffer_pos, this->map_id);

    return this->buffer_pos;
}

void PacketCharacterMapEnter::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->map_id = reader.ReadShort(buffer, this->buffer_pos);
}

PacketCharacterMapLeave::PacketCharacterMapLeave() : PacketBase(PacketBase::PACKET_CHARACTER_MAP_LEAVE)
{}

unsigned int PacketCharacterMapLeave::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteShort(buffer, this->buffer_pos, this->map_id);

    return this->buffer_pos;
}

void PacketCharacterMapLeave::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->map_id = reader.ReadShort(buffer, this->buffer_pos);
}

PacketCharacterTurn::PacketCharacterTurn() : PacketBase(PacketBase::PACKET_CHARACTER_TURN)
{}

unsigned int PacketCharacterTurn::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteByte(buffer, this->buffer_pos, this->direction);

    return this->buffer_pos;
}

void PacketCharacterTurn::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->direction = reader.ReadByte(buffer, this->buffer_pos);
}

PacketCharacterWalk::PacketCharacterWalk() : PacketBase(PacketBase::PACKET_CHARACTER_WALK)
{}

unsigned int PacketCharacterWalk::Encode(char* buffer)
{
    PacketBase::Encode(buffer);

    PacketReader reader;
    reader.WriteInt(buffer, this->buffer_pos, this->character_id);
    reader.WriteShort(buffer, this->buffer_pos, this->from_x);
    reader.WriteShort(buffer, this->buffer_pos, this->from_y);
    reader.WriteShort(buffer, this->buffer_pos, this->to_x);
    reader.WriteShort(buffer, this->buffer_pos, this->to_y);
    reader.WriteByte(buffer, this->buffer_pos, this->direction);

    return this->buffer_pos;
}

void PacketCharacterWalk::Decode(char* buffer)
{
    PacketBase::Decode(buffer);

    PacketReader reader;
    this->character_id = reader.ReadInt(buffer, this->buffer_pos);
    this->from_x = reader.ReadShort(buffer, this->buffer_pos);
    this->from_y = reader.ReadShort(buffer, this->buffer_pos);
    this->to_x = reader.ReadShort(buffer, this->buffer_pos);
    this->to_y = reader.ReadShort(buffer, this->buffer_pos);
    this->direction = reader.ReadByte(buffer, this->buffer_pos);
}

PacketCharacterCreationRequest::PacketCharacterCreationRequest():PacketBase(PACKET_CHARACTER_CREATE_REQUEST), name(""), skin(0), hair(0), hairColor(0), gender(0){}

unsigned int PacketCharacterCreationRequest::Encode(char * buffer)
{
    PacketBase::Encode(buffer);
    const char * name_buffer = this->name.c_str();
    uint8_t name_length = this->name.size();

    PacketReader reader;

    reader.WriteByte(buffer, this->buffer_pos, this->skin);
    reader.WriteByte(buffer, this->buffer_pos, this->hair);
    reader.WriteByte(buffer, this->buffer_pos, this->hairColor);
    reader.WriteByte(buffer, this->buffer_pos, this->gender);
    reader.WriteByte(buffer, this->buffer_pos, name_length);

    for (uint8_t c = 0; c < name_length ; c++)
    {
        reader.WriteByte(buffer, this->buffer_pos, name_buffer[c]);
    }

    return this->buffer_pos;
}

void PacketCharacterCreationRequest::Decode(char * buffer)
{
    PacketBase::Decode(buffer);
    uint8_t name_length = 0;

    PacketReader reader;

    this->skin = reader.ReadByte(buffer, this->buffer_pos);
    this->hair = reader.ReadByte(buffer, this->buffer_pos);
    this->hairColor = reader.ReadByte(buffer, this->buffer_pos);
    this->gender = reader.ReadByte(buffer, this->buffer_pos);
    name_length = reader.ReadByte(buffer, this->buffer_pos);
    for (uint8_t c = 0; c < name_length ; c++)
    {
        this->name += static_cast<char>(reader.ReadByte(buffer, this->buffer_pos));
    }
}

unsigned int PacketCharacterCreationResponse::Encode(char* buffer)
{
    PacketReader reader;
    PacketBase::Encode(buffer);
    reader.WriteByte(buffer, buffer_pos, static_cast<uint8_t>(returnCode));
    return buffer_pos;
}

void PacketCharacterCreationResponse::Decode(char* buffer)
{
    PacketReader reader;
    PacketBase::Decode(buffer);
    returnCode = static_cast<Response>(reader.ReadByte(buffer, buffer_pos));
}
