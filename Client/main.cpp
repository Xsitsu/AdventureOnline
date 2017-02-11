#include <iostream>

#include "GameShared/socket.hpp"

#include "game.hpp"

int main(int argc, char** argv)
{
    InitializeSockets();

    Game game;
    game.Init();
    game.Run();

	ShutdownSockets();

	return 0;
}
