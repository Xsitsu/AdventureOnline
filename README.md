# Adventure Online
A 2D isometric online game written in C++ using the Allegro 5 game programming library.

This project was part of a year long team based Junior Project for junior year of college.

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

## Notes
This repository was migrated from the original repository located at GitLab.

The art assets and sprites used in this project were "borrowed" from an old, obscure game known as "Endless Online". In fact, this game itself was based on the features present in that game.
