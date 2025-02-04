set(target "util")

add_library(${target} STATIC
    filebase.cpp
    filebase.hpp

    resource.cpp
    resource.hpp
    resourcefile.cpp
    resourcefile.hpp

    timer.cpp
    timer.hpp

    vector2.cpp
    vector2.hpp
)

target_include_directories(${target}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

project_dll_export(${target})
