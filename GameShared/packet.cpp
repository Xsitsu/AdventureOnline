#include "packet.hpp"

#include <iostream>

char first = 'E';   //Endless
char second = 'R';  //Rebirth
char third = 'P';   //Packet
char fourth = 'F';  //Format

unsigned int data = (first << 24) | (second < 16) | (third << 8) | fourth;

const unsigned int PacketBase::MAX_BUFFER = 1024;
const unsigned int PacketBase::PACKET_PREFIX = data;

PacketBase::PacketBase() : type(PacketBase::PACKET_UNKNOWN)
{}

PacketBase::PacketBase(PacketBase::PacketType type) : type(type)
{}

unsigned int PacketBase::Encode(char* buffer)
{
    PacketReader reader;

    this->buffer_pos = 0;
    reader.WriteInt(buffer, this->buffer_pos, PacketBase::PACKET_PREFIX);
    reader.WritePacketType(buffer, this->buffer_pos, this->type);
    reader.WriteLongInt(buffer, this->buffer_pos, this->connection_id);
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
    this->connection_id = reader.ReadLongInt(buffer, this->buffer_pos);
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

PacketInitResponse::PacketInitResponse() : PacketBase(PacketBase::PACKET_INIT_RESPONSE), assigned_connection_id(0)
{}

void PacketInitResponse::AssignConnectionId(unsigned long int id)
{
    this->assigned_connection_id = id;
}

unsigned int PacketInitResponse::Encode(char* buffer)
{
    PacketBase::Encode(buffer);
    PacketReader reader;
    reader.WriteLongInt(buffer, this->buffer_pos, this->assigned_connection_id);

    return this->buffer_pos;
}

void PacketInitResponse::Decode(char* buffer)
{
    PacketBase::Decode(buffer);
    PacketReader reader;
    this->assigned_connection_id = reader.ReadLongInt(buffer, this->buffer_pos);
}

PacketDisconnect::PacketDisconnect() : PacketBase(PacketBase::PACKET_DISCONNECT)
{}

PacketDisconnectResponse::PacketDisconnectResponse() : PacketBase(PacketBase::PACKET_DISCONNECT_RESPONSE)
{}

PacketPing::PacketPing() : PacketBase(PacketBase::PACKET_PING)
{}

PacketPong::PacketPong() : PacketBase(PacketBase::PACKET_PONG)
{}


