#ifndef PACKET_HPP_INCLUDE
#define PACKET_HPP_INCLUDE

#include "main.h"

#include <stdint.h>

#include "socket.hpp"

class DLL_EXPORT PacketBase
{
public:
    static const unsigned int MAX_BUFFER;
    static const unsigned int PACKET_PREFIX;
    enum PacketType
    {
        PACKET_UNKNOWN,
        PACKET_INIT,
        PACKET_INIT_RESPONSE,
        PACKET_DISCONNECT,
        PACKET_DISCONNECT_RESPONSE,
        PACKET_PING,
        PACKET_PONG
    };

protected:
    unsigned int buffer_pos;

    bool needs_ack;

protected: // Packet Data
    PacketType type;
    unsigned int connection_id;
    unsigned int sequence;
    unsigned int ack;
    unsigned int ack_bitfield;

public:
    PacketBase();
    PacketBase(PacketType type);
    PacketBase(PacketType type, bool needs_ack);
    virtual ~PacketBase() {}

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    PacketType GetType() { return this->type; }
    unsigned int GetConnectionId() { return this->connection_id; }
    unsigned int GetSequence() { return this->sequence; }
    unsigned int GetAck() { return this->ack; }
    unsigned int GetAckBitfield() { return this->ack_bitfield; }

    void SetConnectionId(unsigned int connection_id) { this->connection_id = connection_id; }
    void SetSequence(unsigned int sequence) { this->sequence = sequence; }
    void SetAck(unsigned int ack) { this->ack = ack; }
    void SetAckBitfield(unsigned int ack_bitfield) { this->ack_bitfield = ack_bitfield; }


    bool GetNeedsAck() { return this->needs_ack; }
    bool SetNeedsAck() { return this->needs_ack; }

};


// This is named PacketReader, but it actually handles both reading and writing of packets.
class DLL_EXPORT PacketReader
{
protected:

public:
    PacketBase* ReadPacket(char* buffer, int bytes_read);

    void WritePacketType(char* buffer, unsigned int& pos, PacketBase::PacketType type);
    PacketBase::PacketType ReadPacketType(char* buffer, unsigned int& pos);

    void WriteInt(char* buffer, unsigned int& pos, uint32_t value);
    uint32_t ReadInt(char* buffer, unsigned int& pos);

    void WriteLongInt(char* buffer, unsigned int& pos, uint64_t value);
    uint64_t ReadLongInt(char* buffer, unsigned int& pos);

    void WriteShort(char* buffer, unsigned int& pos, uint16_t value);
    uint16_t ReadShort(char* buffer, unsigned int& pos);
};


/*
    Packet Implementation Classes
*/


// PacketInit
class DLL_EXPORT PacketInit : public PacketBase
{
protected:
    unsigned short listen_port;

public:
    PacketInit();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    unsigned short GetListenPort() { return this->listen_port; }
    void SetListenPort(unsigned short listen_port) { this->listen_port = listen_port; }
};

// PacketInitResponse
class DLL_EXPORT PacketInitResponse : public PacketBase
{
protected:
    unsigned int assigned_connection_id;

public:
    PacketInitResponse();
    void AssignConnectionId(unsigned int id) { this->assigned_connection_id = id; }
    unsigned int GetAssignedConnectionId() {return this->assigned_connection_id; }

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};

// PacketDisconnect
class DLL_EXPORT PacketDisconnect : public PacketBase
{
protected:

public:
    PacketDisconnect();
};

// PacketDisconnectResponse
class DLL_EXPORT PacketDisconnectResponse : public PacketBase
{
protected:

public:
    PacketDisconnectResponse();
};

// PacketPing
class DLL_EXPORT PacketPing : public PacketBase
{
protected:

public:
    PacketPing();
};

// PacketPong
class DLL_EXPORT PacketPong : public PacketBase
{
protected:

public:
    PacketPong();
};

#endif // PACKET_HPP_INCLUDE
