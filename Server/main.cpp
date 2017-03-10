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

/*
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
*/
