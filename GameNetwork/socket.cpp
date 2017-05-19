#include "socket.hpp"

#include <string>
#include <sstream>

bool InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSADATA WsaData;
	return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
	return true;
#endif
}

void ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}


Address::Address() : address(0), port(0)
{}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) : address(0), port(port)
{
	address = (a << 24) | (b << 16) | (c << 8) | d;
}

Address::Address(unsigned int address, unsigned short port) : address(address), port(port)
{}

unsigned int Address::GetAddress() const
{
	return this->address;
}

unsigned char Address::GetA() const
{
	unsigned int shifter = 255;
	return (this->address >> 24) & shifter;
}

unsigned char Address::GetB() const
{
	unsigned int shifter = 255;
	return (this->address >> 16) & shifter;
}

unsigned char Address::GetC() const
{
	unsigned int shifter = 255;
	return (this->address >> 8) & shifter;
}

unsigned char Address::GetD() const
{
	unsigned int shifter = 255;
	return this->address & shifter;
}

unsigned short Address::GetPort() const
{
	return this->port;
}

sockaddr_in Address::ToSockaddr_in() const
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(this->GetAddress());
	addr.sin_port = htons(this->GetPort());

	return addr;
}

std::string Address::ToString() const
{
    std::stringstream stream;

    stream << (int)this->GetA() << "." << (int)this->GetB() << "."
        << (int)this->GetC() << "." << (int)this->GetD() << ":"
        << (int)this->GetPort();

    return stream.str();
}

bool Address::operator==(const Address& rhs)
{
    return (this->address == rhs.address) && (this->port == rhs.port);
}



Socket::Socket() : handle(0)
{}

Socket::~Socket()
{}

bool Socket::Open(unsigned short port, bool is_server)
{
    is_server = true;

	if (this->IsOpen())
	{
		return false;
	}

	this->handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (!this->IsOpen())
	{
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (is_server)
    {
        if (bind(this->handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
        {
            std::cout << "Failed to bind." << std::endl;
            this->handle = 0;
            return false;
        }
    }


#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	int nonBlocking = 1;
	if (fcntl(this->handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		this->handle = 0;
		return false;
	}

#elif PLATFORM == PLATFORM_WINDOWS
	DWORD nonBlocking = 1;
	if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
	{
		this->handle = 0;
		return false;
	}

#endif

    std::cout << "Successfully opened socket!" << std::endl;
	return true;
}

void Socket::Close()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	close(this->handle);
#elif PLATFORM == PLATFORM_WINDOWS
	closesocket(this->handle);
#endif
}

bool Socket::IsOpen() const
{
	return (handle > 0);
}

bool Socket::Send(const Address& destination, const void* data, int size)
{
	sockaddr_in addr = destination.ToSockaddr_in();

	int sent_bytes = sendto(this->handle, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
	return (sent_bytes == size);
}

int Socket::Receive(Address& sender, void* data, int size)
{
#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = recvfrom(this->handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	sender = Address((unsigned int)ntohl(from.sin_addr.s_addr), (unsigned short)ntohs(from.sin_port));

	return bytes;
}




