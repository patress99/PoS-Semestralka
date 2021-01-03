## PATRES
cmake_minimum_required(VERSION 3.1)

project(PoS_Semka)

## If you want to link SFML statically
 set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
 set(SFML_DIR "C:/SFML/lib/cmake/SFML")

## CREDIT JURAJ SIBIK
set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(SFML 2.5 COMPONENTS graphics audio network REQUIRED)
add_executable(PoS_Semka server.cpp client.cpp main.cpp Game.cpp Game.h Hrac.cpp Hrac.h)
target_link_libraries(PoS_Semka sfml-graphics sfml-audio sfml-network)