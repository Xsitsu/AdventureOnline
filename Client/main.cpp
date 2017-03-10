#include <iostream>

#include "GameNetwork/socket.hpp"

#include "game.hpp"

int main(int argc, char** argv)
{
    InitializeSockets();

    Game::Instance()->Init();
    Game::Instance()->Run();
    Game::Instance()->Cleanup();

	ShutdownSockets();

	return 0;
}
