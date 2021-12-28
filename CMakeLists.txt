cmake_minimum_required(VERSION 3.16)

project(obsession VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")


FILE (
    GLOB
    SOURCES
    "src/main.cpp"
    "src/board.h"
    )

include_directories(obsession src)

add_executable(obsession ${SOURCES})

