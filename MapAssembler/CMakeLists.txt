set(target "mapassembler")

add_executable(${target}
    mapgenfunctions.hpp
    mapgen1.cpp
    mapgen2.cpp

    maphelpfunctions.cpp
    maphelpfunctions.hpp

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
)
