set(target "gameworld")

add_library(${target} STATIC
    actor.cpp
    actor.hpp

    actormanager.hpp

    actorstate.hpp
    actorstateattack.cpp
    actorstatedead.cpp
    actorstaterevive.cpp
    actorstatestand.cpp
    actorstateturn.cpp
    actorstatewalk.cpp

    character.cpp
    character.hpp

    map.cpp
    map.hpp

    mapfile.cpp
    mapfile.hpp

    mapmanager.hpp

    maptile.cpp
    maptile.hpp

    mapwarp.hpp
    mapwarpbase.cpp
    mapwarpregular.cpp
    mapwarpregular.hpp
)

target_include_directories(${target}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

project_dll_export(${target})
