cmake_minimum_required(VERSION 3.10)
project(order_book_sim)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(sim main.cpp)