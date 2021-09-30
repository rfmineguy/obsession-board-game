cmake_minimum_required(VERSION 3.16)

project(obsession VERSION 1.0.0.0)

FILE (
    GLOB
    SOURCES
    "src/main.cpp"
    "src/board.cpp"
    "src/side.hpp"
    "src/board.hpp"
    )

add_executable(obsession ${SOURCES})
