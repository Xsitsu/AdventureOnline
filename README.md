# Adventure Online
A 2D isometric online game written in C++ using the Allegro 5 game programming library.

This project was part of a year long team based Junior Project for junior year of college.

This project was originally written in 2017 with Allegro 5.0.10, and last updated in 2020 to be usable with Allegro 5.2.

## Game Features
**Account Management:** Users are able to to register for accounts and login to the game.

**Character Management:** Users are able to create and delete characters, and customize them with details including name, gender, and hair.

**Game World:** The game takes place on an isometric grid within various world maps. Characters are able to move between different maps via warp tiles.

**Combat:** Characters are able to engage in basic combat with each other.

## Technical Features
**Database:** Uses an SQL database to store user data.

**Resource Files:** Created custom binary resource file types that the game would load at runtime. Included data ranging from sprites to map data.

**Networking:** Used UDP sockets with custom packet checking to ensure commands were properly relayed from client to server to client and that no important information was lossed or received out of sequence.

**Project File Split:** The solution is split into different project files that build into DLLs that are ultimately used in either the Client or Server project to compile the full game.

**UI Component System:** Allegro 5 provides methods for drawing and transforming images and primitive shapes. We built upon this a basic UI component system that would respond to events such as mouse hover, mouse click, and text input. The UI system could also load and unload different UI Screens in a stack.

## Technology
The [Code::Blocks](http://www.codeblocks.org/) IDE with the MinGW compiler was used for development of this project.

The [Allegro 5](http://liballeg.org/) game programming library was used in the development of this game to handle window/display creation, input events, and image/sprite drawing.

## Building
### Windows
1. Clone the repository.
2. Get a copy of [Allegro 5.2](https://github.com/liballeg/allegro5/releases) and put it into the newly copied repository directory.
3. Install **the same exact version** of the MinGW compiler that was used to compile the binaries for your copy of Allegro, and setup Code::Blocks to use this compiler.
4. Open the AdventureOnline.workspace file in Code::Blocks.
5. Build Client, Server, and MapAssembler. (You will receive errors)
6. Build FileMaker, GameWorld, and GameGui. (You will receive errors)
7. Build GameNetwork, and GameUtil.
8. Build FileMaker, GameWorld, and GameGui.
9. Build Client, Server, and MapAssembler.
10. Client, Server, and FileMaker will need the appropriate allegro_monolith DLL file moved into their bin folders. This will be **allegro_monolith-debug-5.2** for debug and **allegro_monolith-5.2** for release.
11. Client, Server, FileMaker, and MapAssembler, may require DLLs with names similar to **libgcc** and **libstdc++**. These should be able to be found in the directory where your compiler was installed and can be copied and moved into the respective bin folders.

**Note:** This build order in steps 5 through 9 is required for post build scripts that automatically move DLLs into necessary folders. This build order ensures that the destination folders will actually exist. This could be fixed with a better build script, but it wont be for now.

### Linux
Although Linux support is present in the codebase, the loss of the project's Makefiles means that there is unfortunately no official way to build this project at this time.

## Setting Up
After building the project, you will have both the Client and Server, but it wont do you much good without the necessary resource, map, and database files.

### Resource Files
1. Clone the [AO Resource](https://github.com/Xsitsu/AO-Resource/) repository.
2. Open FileMaker/main.cpp and change line 85 to set the correct fully qualified path to the newly cloned AO-Resource repository.
3. Build and run the FileMaker program.
4. If all went correct, FileMaker will output .aorf files in its same directory. You can copy these files into the same directory as the Client program.

### Map Files
1. Run the MapAssembler program and it will automatically create .aomf files.
2. Copy and move the new .aomf files into the directories for Server and Client.

**Note:** There is no official map editor for this game. Map files are generated from hand crafted functions. It is possible to write new functions to create entirely new maps. The only requirement is that both the Server and any Clients connecting to it must have the same map files.

### Database
1. Copy AO.db from the Server directory and move it into the directory where you will run the Server program from.

**Note:** There is a repository for [Adventure Online Database](https://github.com/Xsitsu/AdventureOnlineDatabase) SQL files, however they were never properly integrated with sqlite3 and are not working.

### Server Configuration
There is no config file for server setup and configuration. You must manually edit these settings.

**Port:** Server/main.cpp line 13. You can edit the variable here for the port the server will listen on.

**Max Accepted Connections:** Server/main.cpp line 14. It is not named, however it is the second variable passed to the constructor for the Server class. The default is 500, after which the server will refuse any more.

### Client Configuration
There is no config file for client setup and configuration. You must manually edit these settings.

**Server Address:** Client/game.cpp line 70. There are five numbers passed to the Address object. The first four are an IPv4 address formatted as follows **127.0.0.1** and the fifth is the port to connect to. If you want to run a server on a dedicated machine then you will need to change the address here to connect to the server. The port must be the same port that the server is listening on.

**Listen Port:** Client/game.cpp line 69. The default port that the client will attempt to listen on when connecting with the server. If the port is unavailable, the client will increment and try again with the next port. This is to allow multiple clients to connect from the same machine.

### Setup Complete
You should now be able to play the game!

## Notes
This repository was migrated from the original repository located at GitLab.

The art assets and sprites used in this project were "borrowed" from an old, obscure game known as "Endless Online". In fact, this game itself was based on the features present in that game.
