cmake_minimum_required(VERSION 4.1)
project(my_ls)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_executable(my_ls main.cpp
        printDir.cpp
        printDir.h
        printDirSubordiante.cpp
        colors.cpp
)
