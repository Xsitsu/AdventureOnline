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
    Player * testPlayer = new Player(-1, "Jose@oit.edu", "salt", "hash");
    database.CreatePlayer(testPlayer);
    std::cout << testPlayer->GetID() << std::endl;
    delete testPlayer;
    testPlayer = new Player( database.ReadPlayer("Jose@oit.edu") );
    std::cout << testPlayer->GetEmailAddress() << testPlayer->GetID() << testPlayer->GetSalt() << testPlayer->GetHash() << std::endl;
    testPlayer->SetHash("nohash!");
    database.UpdatePlayer(testPlayer);
    std::cout << testPlayer->GetEmailAddress() << testPlayer->GetID() << testPlayer->GetSalt() << testPlayer->GetHash() << std::endl;
    database.DeletePlayer(testPlayer);
    delete testPlayer;
}
