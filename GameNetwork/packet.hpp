#ifndef PACKET_HPP_INCLUDE
#define PACKET_HPP_INCLUDE

#include "main.h"

#include <stdint.h>
#include <string>
#include <vector>

#include "GameWorld/character.hpp"
#include "socket.hpp"

using std::string;

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
        PACKET_PONG,
        PACKET_REGISTRATION_REQUEST,
        PACKET_REGISTRATION_RESPONSE,
        PACKET_LOGIN_REQUEST,
        PACKET_LOGIN_RESPONSE,
        PACKET_CHARACTER_LIST_REQUEST,
        PACKET_CHARACTER,
        PACKET_LOGOUT
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
    void SetNeedsAck(bool val) { this->needs_ack = val; }

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

    void WriteByte(char* buffer, unsigned int& pos, uint8_t value);
    uint8_t ReadByte(char* buffer, unsigned int& pos);
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
    bool connection_accepted;
    unsigned int assigned_connection_id;

public:
    PacketInitResponse();
    void AssignConnectionId(unsigned int id) { this->assigned_connection_id = id; }
    unsigned int GetAssignedConnectionId() {return this->assigned_connection_id; }

    void SetConnectionAccepted(bool accepted) { this->connection_accepted = accepted; }
    bool GetConnectionAccepted() { return this->connection_accepted; }

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

class DLL_EXPORT PacketRegistrationRequest: public PacketBase
{
protected:
    std::string p_email;
    std::string p_password;
    uint8_t email_length;
    uint8_t password_length;



public:
    PacketRegistrationRequest();

    std::string GetEmail();
    std::string GetPassword();
    void SetEmail( string email );
    void SetPassword( string password );

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};


class DLL_EXPORT PacketRegistrationResponse : public PacketBase
{


public:
    enum Response
    {
        RESPONSE_ACCOUNT_CREATED,
        RESPONSE_ACCOUNT_ALREADY_EXISTS,
        RESPONSE_ERROR
    };
    PacketRegistrationResponse();

    Response GetResponse();
    void SetResponse(Response);

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);



protected:
    Response returnCode;
};

class DLL_EXPORT PacketLoginRequest : public PacketBase
{
protected:
    uint8_t email_length;
    uint8_t password_length;
    std::string email;
    std::string password;

public:
    PacketLoginRequest();

    std::string GetEmail() { return this->email; }
    std::string GetPassword() { return this->password; }
    void SetEmail(std::string email);
    void SetPassword(std::string password);

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};


class DLL_EXPORT PacketLoginResponse : public PacketBase
{
public:
    enum LoginResponse
    {
        LOGINRESPONSE_SUCCESS,
        LOGINRESPONSE_FAIL,
        LOGINRESPONSE_ALREADY_LOGGED_IN,
        LOGINRESPONSE_ERROR
    };
protected:
    LoginResponse response;

public:
    PacketLoginResponse();

    void SetResponse(LoginResponse response) { this->response = response; }
    LoginResponse GetResponse() { return this->response; }

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};


class DLL_EXPORT PacketCharacterListRequest : public PacketBase
{
public:
    PacketCharacterListRequest();
};

class DLL_EXPORT PacketCharacter : public PacketBase
{
public:
    PacketCharacter(Character * info = nullptr);

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    Character* GetCharacter();
    uint8_t GetMap() {return mapID;}
    uint8_t GetPosX() { return pos_x; }
    uint8_t GetPosY() { return pos_y; }
    Actor::Direction GetDirection() { return static_cast<Actor::Direction>(direction); }
    uint8_t GetHealth() { return health; }
    uint8_t GetMaxHealth() { return maxHealth; }
    uint8_t GetStrength() { return strength; }
    uint8_t GetEndurance() { return endurance; }
    std::string GetName() { return name; }
    Character::Gender GetGender() { return static_cast<Character::Gender>(gender); }
    Character::Skin GetSkin() { return static_cast<Character::Skin>(skin); }

    void SetMap( uint8_t val ) { mapID = val; }
    void SetPosX( uint8_t val ) { pos_x = val; }
    void SetPosY( uint8_t val ) { pos_y = val; }
    void SetDirection( Actor::Direction val ) { direction = static_cast<uint8_t>(val); }
    void SetHealth( uint8_t val ) { health = val; }
    void SetMaxHealth( uint8_t val ) { maxHealth = val; }
    void SetStrength( uint8_t val ) { strength = val; }
    void SetEndurance( uint8_t val ) { endurance = val; }
    void SetName( std::string val ) { name = val; }
    void SetGender( Character::Gender val ) { gender = static_cast<uint8_t>(val); }
    void SetSkin( Character::Skin val ) { skin = static_cast<uint8_t>(val); }


//    Character GetCharacters() { return character; }
//    void SetCharacters(Character val) { character = val; }
protected:
    uint8_t mapID;
    uint8_t pos_x;
    uint8_t pos_y;
    uint8_t direction;
    uint8_t health;
    uint8_t maxHealth;
    uint8_t strength;
    uint8_t endurance;

    std::string name;
    uint8_t gender;
    uint8_t skin;
};

class DLL_EXPORT PacketLogout : public PacketBase
{
protected:

public:
    PacketLogout();
};

#endif // PACKET_HPP_INCLUDE
