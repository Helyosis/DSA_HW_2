cmake_minimum_required(VERSION 3.22)
project(Project)

add_compile_options(-fsized-deallocation)
set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp Graph.cpp Graph.h Game.cpp Game.h)
