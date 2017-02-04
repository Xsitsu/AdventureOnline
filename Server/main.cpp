#include <iostream>

#include "GameShared/socket.hpp"

#include "server.hpp"

int main(int argc, char** argv)
{
    InitializeSockets();

    const short port = 50000;
    Server server(port);
    server.Init();

    std::cout << "Server started." << std::endl
                << "Waiting for connections..." << std::endl << std::endl;
    while(true)
    {
        server.Tick();
    }

    ShutdownSockets();
}
