cmake_minimum_required(VERSION 3.16)
project(OrderBookSim)
set(CMAKE_CXX_STANDARD)

add_subdirectory(graph)
add_subdirectory(orderbook)
add_subdirectory(traders)

add_executable(orderBookSim main.cpp)
target_link_libraries(orderBookSim PRIVATE 
    graph
    orderbook
    traders
)