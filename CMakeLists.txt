cmake_minimum_required(VERSION 3.10)
project(OrderBookSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(myapp main.cpp)

# Recursively gather all cpp files under src directory
file(GLOB_RECURSE SRC_FILES src/*.cpp)

target_sources(myapp PRIVATE ${SRC_FILES})

target_include_directories(myapp PRIVATE include)
