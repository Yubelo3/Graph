cmake_minimum_required(VERSION 3.9)

project(Booster)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(Booster src/main.cpp src/Graph.cpp src/Brute_Force.hpp src/Greedy.hpp)