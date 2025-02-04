cmake_minimum_required(VERSION 3.17)

project(AdventureOnline VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_BINARY_DIR}/CPM_modules")

include(GNUInstallDirs)  # https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}" CACHE PATH ".lib, .a, etc.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}" CACHE PATH ".so, .dylib, etc.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}" CACHE PATH ".exe, .dll, etc.")

include(DllExport)

file(REAL_PATH "${PROJECT_BINARY_DIR}/../_dependency-cache" CPM_SOURCE_CACHE)

include(cpm)  # CPM.cmake has to come before dependencies

include(allegro)

include_directories(${CMAKE_CURRENT_LIST_DIR})

#add_subdirectory(Client)
#add_subdirectory(FileMaker)
#add_subdirectory(GameGui)
#add_subdirectory(GameNetwork)
add_subdirectory(GameUtil)
add_subdirectory(GameWorld)
add_subdirectory(MapAssembler)
#add_subdirectory(Server)
