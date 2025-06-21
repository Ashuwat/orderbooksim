cmake_minimum_required(VERSION 3.16)
project(OrderBookSim)
set(CMAKE_CXX_STANDARD)

add_subdirectory(src)

add_executable(orderBookSim main.cpp)
target_link_libraries(orderBookSim PRIVATE orderbook trading)