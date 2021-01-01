cmake_minimum_required(VERSION 3.7)
project(PoS_Semka)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(PoS_Semka main.cpp)
