#include <iostream>

#include <exception>

#include "GameShared/socket.hpp"

#include "server.hpp"
#include "DB_Bridge.h"
void testCode();        //function to test classes incrementally

int main(int argc, char** argv)
{
    testCode();
    InitializeSockets();

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

void testCode()
{
    DB_Bridge   database;
    database.CreatePlayer(new Player(-1, "Jose@oit.edu", "salt", "hash"));

}
