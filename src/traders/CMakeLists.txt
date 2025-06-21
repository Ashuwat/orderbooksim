add_library(traders
    traders.cpp
)

target_include_directories(traders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(traders PUBLIC orderbook)