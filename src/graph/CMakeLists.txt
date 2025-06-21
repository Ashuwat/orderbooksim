add_library(graph
    traderGraph.cpp
)

target_include_directories(graph
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)