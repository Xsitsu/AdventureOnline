#include <iostream>

#include <exception>

#include "GameShared/socket.hpp"

#include "server.hpp"
#include "DB_Bridge.h"
void testCode();        //function to test classes incrementally

int main(int argc, char** argv)
{
<<<<<<< HEAD
    //testCode();   //debug code
=======
    //testCode();   //debug code
>>>>>>> da960841c06c241b7078dd2f2bf4c51244bfe2f9
    InitializeSockets();

    const short port = 50000;
    Server server(port, 500);
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
    //std::cout << testPlayer->GetID() << std::endl; //debug output
    delete testPlayer;
    testPlayer = new Player( database.ReadPlayer("Jose@oit.edu") );
    //std::cout << testPlayer->GetEmailAddress() << testPlayer->GetID() << testPlayer->GetSalt() << testPlayer->GetHash() << std::endl; //debug output
    testPlayer->SetHash("nohash!");
    database.UpdatePlayer(testPlayer);
    //std::cout << testPlayer->GetEmailAddress() << testPlayer->GetID() << testPlayer->GetSalt() << testPlayer->GetHash() << std::endl;//debug output
    database.DeletePlayer(testPlayer);
    delete testPlayer;

    PlayerCharacter * testCharacter = new PlayerCharacter(55, "Jose the Eight", 10, 12, 1, 23, 24, 25);
    database.CreatePlayerCharacter(testCharacter);
    delete testCharacter;
}
