set(target "server")

add_executable(${target}
    account.cpp
    account.hpp

    accountservice.cpp
    accountservice.hpp

    actormanagercharacter.cpp
    actormanagercharacter.hpp

    clientconnection.cpp
    clientconnection.hpp

    clientstate.hpp
    clientstatebase.cpp
    clientstateinit.cpp
    clientstateloggedin.cpp
    clientstatenologin.cpp
    clientstateplaying.cpp

    database.cpp
    database.hpp

    mapmanagerworld.cpp
    mapmanagerworld.hpp

    server.cpp
    server.hpp

    sqlite3.c
    sqlite3.h

    world.cpp
    world.hpp

    main.cpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		gameworld
		util
        network
)
