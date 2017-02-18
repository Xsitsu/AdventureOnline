#include <iostream>

#include <exception>

#include "GameShared/socket.hpp"

#include "server.hpp"
#include "include/DB_Bridge.h"

int main(int argc, char** argv)
{
    DB_Bridge   database;
    InitializeSockets();
    std::cout << database.GetReturnCode() << std::endl;

    const short port = 50000;
    Server server(port, 2);
    server.Init();

    std::cout << "Server started." << std::endl
                << "Waiting for connections..." << std::endl << std::endl;
    while(true)
    {
        server.Tick();
    }

    ShutdownSockets();
}
