cmake_minimum_required(VERSION 4.1)
project(my_ls)

set(CMAKE_CXX_STANDARD 20)

add_executable(my_ls main.cpp
        printDir.cpp
)
