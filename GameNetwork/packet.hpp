#ifndef PACKET_HPP_INCLUDE
#define PACKET_HPP_INCLUDE

#include "main.h"

#include <stdint.h>
#include <string>
#include <list>

#include "socket.hpp"

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketBase
{
public:
    static const unsigned int MAX_BUFFER;
    static const unsigned int PACKET_PREFIX;
    enum PacketType
    {
        PACKET_UNKNOWN = 0,
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
        PACKET_LOGOUT,
        PACKET_CHARACTER_LIST_REQUEST,
        PACKET_CHARACTER_LIST,
        PACKET_CHARACTER_DATA_REQUEST,
        PACKET_CHARACTER_LOGIN,
        PACKET_CHARACTER_LOGOUT,
        PACKET_CHARACTER_APPEARANCE,
        PACKET_CHARACTER_POSITION,
        PACKET_CHARACTER_STATS,

        PACKET_CHARACTER_MAP_ENTER,
        PACKET_CHARACTER_MAP_LEAVE,

        PACKET_CHARACTER_TURN,
        PACKET_CHARACTER_WALK,
        PACKET_CHARACTER_ATTACK,
        PACKET_CHARACTER_TAKE_DAMAGE,
        PACKET_CHARACTER_DIED,

        PACKET_CHARACTER_CREATE_REQUEST,
        PACKET_CHARACTER_CREATE_RESPONSE
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
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketReader
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
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketInit : public PacketBase
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
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketInitResponse : public PacketBase
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
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketDisconnect : public PacketBase
{
protected:

public:
    PacketDisconnect();
};

// PacketDisconnectResponse
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketDisconnectResponse : public PacketBase
{
protected:

public:
    PacketDisconnectResponse();
};

// PacketPing
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketPing : public PacketBase
{
protected:

public:
    PacketPing();
};

// PacketPong
class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketPong : public PacketBase
{
protected:

public:
    PacketPong();
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketRegistrationRequest: public PacketBase
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
    void SetEmail(std::string email);
    void SetPassword(std::string password);

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};


class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketRegistrationResponse : public PacketBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketLoginRequest : public PacketBase
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


class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketLoginResponse : public PacketBase
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

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketLogout : public PacketBase
{
protected:

public:
    PacketLogout();
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterListRequest : public PacketBase
{
public:
    PacketCharacterListRequest();
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterList : public PacketBase
{
protected:
    std::list<uint32_t> character_ids;

public:
    PacketCharacterList();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    std::list<uint32_t> GetCharacterList() const;
    void SetCharacterList(std::list<uint32_t> character_ids);
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterDataRequest : public PacketBase
{
public:
    // Used for encoding bools into a single byte
    static const uint8_t BIT_APPEARANCE = 1;    // 00000001
    static const uint8_t BIT_POSITION = 2;      // 00000010
    static const uint8_t BIT_STATS = 4;         // 00000100

protected:
    uint32_t character_id;
    bool request_appearance;
    bool request_position;
    bool request_stats;

public:
    PacketCharacterDataRequest();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const;
    void SetCharacterId(uint32_t character_id);

    bool GetRequestAppearance() const;
    bool GetRequestPosition() const;
    bool GetRequestStats() const;

    void SetRequestAppearance(bool val);
    void SetRequestPosition(bool val);
    void SetRequestStats(bool val);
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterLogin : public PacketBase
{
protected:
    uint32_t character_id;

public:
    PacketCharacterLogin();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const;
    void SetCharacterId(uint32_t character_id);
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterLogout : public PacketBase
{
public:
    PacketCharacterLogout();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterAppearance : public PacketBase
{
protected:
    uint32_t character_id;

    std::string name;
    uint8_t gender;
    uint8_t skin;
    uint8_t hair;
    uint8_t hairColor;

public:
    PacketCharacterAppearance();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const;
    std::string GetName() const;
    uint8_t GetGender() const;
    uint8_t GetSkin() const;
    uint8_t GetHair() const { return hair; }
    uint8_t GetHairColor() const{ return hairColor; }

    void SetCharacterId(uint32_t character_id);
    void SetName(std::string name);
    void SetGender(uint8_t gender);
    void SetSkin(uint8_t skin);
    void SetHair(uint8_t val)   { hair = val;}
    void SetHairColor(uint8_t val) { hairColor = val;}

};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterPosition : public PacketBase
{
protected:
    uint32_t character_id;

    uint16_t map_id;
    uint16_t position_x;
    uint16_t position_y;
    uint8_t direction;

public:
    PacketCharacterPosition();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const;
    uint16_t GetMapId() const;
    uint16_t GetPositionX() const;
    uint16_t GetPositionY() const;
    uint8_t GetDirection() const;

    void SetCharacterId(uint32_t id);
    void SetMapId(uint16_t id);
    void SetPositionX(uint16_t pos_x);
    void SetPositionY(uint16_t pos_y);
    void SetDirection(uint8_t direction);
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterStats : public PacketBase
{
protected:
    uint32_t character_id;

    uint16_t health;
    uint16_t max_health;

public:
    PacketCharacterStats();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    void SetCharacterId(uint32_t character_id) { this->character_id = character_id; }

    uint16_t GetHealth() const { return this->health; }
    void SetHealth(uint16_t health) { this->health = health; }

    uint16_t GetMaxHealth() const { return this->max_health; }
    void SetMaxHealth(uint16_t max_health) { this->max_health = max_health; }

};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterMapEnter : public PacketBase
{
protected:
    uint32_t character_id;
    uint16_t map_id;

public:
    PacketCharacterMapEnter();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    uint16_t GetMapId() const { return this->map_id; }

    void SetCharacterId(uint32_t id) { this->character_id = id; }
    void SetMapId(uint16_t id) { this->map_id = id; }
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterMapLeave : public PacketBase
{
protected:
    uint32_t character_id;
    uint16_t map_id;

public:
    PacketCharacterMapLeave();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    uint16_t GetMapId() const { return this->map_id; }

    void SetCharacterId(uint32_t id) { this->character_id = id; }
    void SetMapId(uint16_t id) { this->map_id = id; }
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterTurn : public PacketBase
{
protected:
    uint32_t character_id;
    uint8_t direction;

public:
    PacketCharacterTurn();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    uint8_t GetDirection() const { return this->direction; }

    void SetCharacterId(uint32_t id) { this->character_id = id; }
    void SetDirection(uint8_t direction) { this->direction = direction; }

};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterWalk : public PacketBase
{
protected:
    uint32_t character_id;

    uint16_t from_x;
    uint16_t from_y;

    uint16_t to_x;
    uint16_t to_y;

    uint8_t direction;

public:
    PacketCharacterWalk();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    uint16_t GetFromX() const { return this->from_x; }
    uint16_t GetFromY() const { return this->from_y; }
    uint16_t GetToX() const { return this->to_x; }
    uint16_t GetToY() const { return this->to_y; }
    uint8_t GetDirection() const { return this->direction; }

    void SetCharacterId(uint32_t id) { this->character_id = id; }
    void SetFromX(uint16_t from_x) { this->from_x = from_x; }
    void SetFromY(uint16_t from_y) { this->from_y = from_y; }
    void SetToX(uint16_t to_x) { this->to_x = to_x; }
    void SetToY(uint16_t to_y) { this->to_y = to_y; }
    void SetDirection(uint8_t direction) { this->direction = direction; }

};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterCreationRequest : public PacketBase
{
protected:
    std::string name;
    uint8_t skin;
    uint8_t hair;
    uint8_t hairColor;
    uint8_t gender;

public:
    PacketCharacterCreationRequest();

    virtual unsigned int Encode(char * buffer);
    virtual void Decode(char * buffer);

    void SetName(std::string val) { name = val; }
    void SetSkin(int val ) { skin = val; }
    void SetHair( int val ) { hair = val; }
    void SetHairColor(int val ) { hairColor = val; }
    void SetGender(int val ) { gender = val;}

    std::string GetName() {return name; }
    int GetSkin() { return skin; }
    int GetHair() { return hair; }
    int GetHairColor() { return hairColor; }
    int GetGender() { return gender; }
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterCreationResponse : public PacketBase
{
public:
    enum Response
    {
        RESPONSE_CHARACTER_CREATED,
        RESPONSE_CHARACTER_ALREADY_EXISTS,
        RESPONSE_ERROR
    };
    PacketCharacterCreationResponse():PacketBase(PACKET_CHARACTER_CREATE_RESPONSE){}

    Response GetResponse() {return returnCode; }
    void SetResponse(Response val) { returnCode = val; }

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

protected:
    Response returnCode;
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterAttack : public PacketBase
{
protected:
    uint32_t character_id;

public:
    PacketCharacterAttack();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    void SetCharacterId(uint32_t character_id) { this->character_id = character_id; }
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterTakeDamage : public PacketBase
{
protected:
    uint32_t character_id;
    uint16_t new_health;
    uint16_t taken_damage;

public:
    PacketCharacterTakeDamage();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    void SetCharacterId(uint32_t character_id) { this->character_id = character_id; }

    uint16_t GetNewHealth() const { return this->new_health; }
    void SetNewHealth(uint16_t new_health) { this->new_health = new_health; }

    uint16_t GetTakenDamage() const { return this->taken_damage; }
    void SetTakenDamage(uint16_t taken_damage) { this->taken_damage = taken_damage; }
};

class
#ifdef WINDOWS
DLL_EXPORT
#endif
PacketCharacterDied : public PacketBase
{
protected:
    uint32_t character_id;

public:
    PacketCharacterDied();

    virtual unsigned int Encode(char* buffer);
    virtual void Decode(char* buffer);

    uint32_t GetCharacterId() const { return this->character_id; }
    void SetCharacterId(uint32_t character_id) { this->character_id = character_id; }
};

#endif // PACKET_HPP_INCLUDE
