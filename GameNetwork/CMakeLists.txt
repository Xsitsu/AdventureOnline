set(target "network")

add_library(${target} STATIC
    packet.cpp
    packet.hpp
    packetacklist.cpp
    packetacklist.hpp
    socket.cpp
    socket.hpp
)

target_include_directories(${target}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${target}
    PRIVATE
        $<$<PLATFORM_ID:Windows>:ws2_32>
)

project_dll_export(${target})
