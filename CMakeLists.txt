cmake_minimum_required(VERSION 3.28)
project(PRNG)

set(CMAKE_CXX_STANDARD 20)

add_executable(PRNG main.cpp
        Generator.h )
