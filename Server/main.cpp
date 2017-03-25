#include <iostream>

#include <exception>

#include "GameNetwork/socket.hpp"

#include "server.hpp"

int main(int argc, char** argv)
{
    InitializeSockets();

    const short port = 50000;
    Server server(port, 500);
    server.Init();
    server.EstablishDatabaseConnection();

    std::cout << "Server started." << std::endl
                << "Waiting for connections..." << std::endl << std::endl;
    while(true)
    {
        server.Tick();
    }

    server.CloseDatabaseConnection();

    ShutdownSockets();
}

