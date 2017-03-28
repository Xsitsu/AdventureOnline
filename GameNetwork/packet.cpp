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
    case PacketBase::PACKET_CHARACTER_LIST_REQUEST:
        packet = new PacketCharacterListRequest();
        break;
    case PacketBase::PACKET_CHARACTER:
        packet = new PacketCharacter();
        break;
    case PacketBase::PACKET_LOGOUT:
        packet = new PacketLogout();
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

string PacketRegistrationRequest::GetEmail()
{
    return p_email;
}

string PacketRegistrationRequest::GetPassword()
{
    return p_password;
}

void PacketRegistrationRequest::SetEmail( string email )
{
    p_email = email;
    email_length = p_email.size();
}

void PacketRegistrationRequest::SetPassword( string password )
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

//unsigned int PacketCharacterListRequest::Encode(char* buffer)
//{
//    this->buffer_pos = 0;
//    PacketBase::Encode(buffer);
//
//    return this->buffer_pos;
//}
//
//void PacketCharacterListRequest::Decode(char* buffer)
//{
//    PacketBase::Decode(buffer);
//}
PacketCharacterListRequest::PacketCharacterListRequest(): PacketBase(PacketBase::PACKET_CHARACTER_LIST_REQUEST) {}

PacketCharacter::PacketCharacter(Character * info ): PacketBase(PacketBase::PACKET_CHARACTER)
{
    if (info)
    {
        name = info->GetName();
        pos_x = info->GetPosition().x;
        pos_y = info->GetPosition().y;
        direction = static_cast<short int>(info->GetDirection());
        health = info->GetHealth();
        maxHealth = info->GetMaxHealth();
        strength = info->GetStrength();
        endurance = info->GetEndurance();

        gender = static_cast<short int>(info->GetGender());
        skin = static_cast<short int>(info->GetSkin());
    }
}

unsigned int PacketCharacter::Encode(char* buffer)
{
    PacketReader reader;
    PacketBase::Encode(buffer);

    uint8_t name_length = name.size();
    const char * encode_name = name.c_str();

    reader.WriteByte(buffer,buffer_pos, mapID);
    reader.WriteByte(buffer,buffer_pos, pos_x);
    reader.WriteByte(buffer,buffer_pos, pos_y);
    reader.WriteByte(buffer,buffer_pos, direction);
    reader.WriteByte(buffer,buffer_pos, health);
    reader.WriteByte(buffer,buffer_pos, maxHealth);
    reader.WriteByte(buffer,buffer_pos, strength);
    reader.WriteByte(buffer,buffer_pos, endurance);
    reader.WriteByte(buffer,buffer_pos, skin);
    reader.WriteByte(buffer,buffer_pos, gender);
    reader.WriteByte(buffer,buffer_pos, name_length);
    for(int i =0; i < name_length; i++)
    {
        reader.WriteByte(buffer, buffer_pos, encode_name[i]);
    }

    return buffer_pos;
}

void PacketCharacter::Decode(char* buffer)
{
    PacketReader reader;
    PacketBase::Decode(buffer);

    Vector2 position;
    char * decode_name;
    uint8_t name_length;


    mapID = reader.ReadByte(buffer, buffer_pos) ;
    pos_x = reader.ReadByte(buffer, buffer_pos) ;
    pos_y = reader.ReadByte(buffer, buffer_pos) ;
    direction = reader.ReadByte(buffer, buffer_pos) ;
    health = reader.ReadByte(buffer, buffer_pos) ;
    maxHealth = reader.ReadByte(buffer, buffer_pos) ;
    strength = reader.ReadByte(buffer, buffer_pos) ;
    endurance = reader.ReadByte(buffer, buffer_pos) ;
    skin = reader.ReadByte(buffer, buffer_pos) ;
    gender = reader.ReadByte(buffer, buffer_pos) ;
    name_length = reader.ReadByte(buffer, buffer_pos);
    decode_name = new char[name_length+1];

    for(int i =0; i < name_length; i++)
    {
        decode_name[i] = reader.ReadByte(buffer, buffer_pos);
    }
    decode_name[name_length] = 0;

    name = decode_name;
    delete[] decode_name;
}

Character* PacketCharacter::GetCharacter()
{
    Character * newborn = new Character();
    newborn->SetName(name);
    newborn->SetGender(static_cast<Character::Gender>(gender));
    newborn->SetSkin(static_cast<Character::Skin>(skin));
    newborn->Warp(nullptr, Vector2(pos_x, pos_y));
    newborn->SetDirection(static_cast<Actor::Direction>(direction));
    newborn->SetHealth(health);
    newborn->SetMaxHealth(maxHealth);
    newborn->SetStrength(strength);
    newborn->SetEndurance(endurance);

    return newborn;
}

PacketLogout::PacketLogout() : PacketBase(PacketBase::PACKET_LOGOUT)
{}
