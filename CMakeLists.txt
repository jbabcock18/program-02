cmake_minimum_required(VERSION 3.15)
project(program_02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set (input01 "commands.txt")

foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
add_executable(program_02
        Graph.h
        main.cpp)
