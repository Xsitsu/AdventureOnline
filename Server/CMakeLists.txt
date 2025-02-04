set(target "server")

add_executable(${target}
    database.cpp
    database.hpp

    mapmanagerworld.cpp
    mapmanagerworld.hpp

    server.cpp
    server.hpp

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
