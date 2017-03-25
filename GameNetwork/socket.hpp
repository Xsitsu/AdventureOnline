#ifndef SOCKET_HPP_INCLUDE
#define SOCKET_HPP_INCLUDE

#include "main.h"

#if PLATFORM == PLATFORM_WINDOWS

#include <winsock2.h>
//#pragma comment(lib,"WS2_32")

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#endif

bool DLL_EXPORT InitializeSockets();
void DLL_EXPORT ShutdownSockets();

class DLL_EXPORT Address
{
public:
	Address();
	Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
	Address(unsigned int address, unsigned short port);
	unsigned int GetAddress() const;
	unsigned char GetA() const;
	unsigned char GetB() const;
	unsigned char GetC() const;
	unsigned char GetD() const;
	unsigned short GetPort() const;

	sockaddr_in ToSockaddr_in() const;

	bool operator==(const Address& rhs);

private:
	unsigned int address;
	unsigned short port;

};

class DLL_EXPORT Socket
{
public:
	Socket();
	~Socket();
	bool Open(unsigned short port, bool is_server = false);
	void Close();
	bool IsOpen() const;
	bool Send(const Address& destination, const void* data, int size);
	int Receive(Address& sender, void* data, int size);

private:
	int handle;
};

#endif //SOCKET_HPP_INCLUDE
