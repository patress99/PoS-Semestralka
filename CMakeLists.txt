cmake_minimum_required(VERSION 3.7)

project(PoS_Semka)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/SEMKA/SFML/lib/cmake/SFML")

set(CMAKE_EXE_LINKER_FLAGS "-static")


find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
add_executable(PoS_Semka main.cpp Game.cpp Game.h Player.cpp Player.h Menu.cpp Menu.h)
target_link_libraries(PoS_Semka sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
