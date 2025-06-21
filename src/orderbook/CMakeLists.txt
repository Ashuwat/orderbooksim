add_library(orderbook
    ledger.cpp
    ask.cpp
    bid.cpp
    ticket.cpp
)

target_include_directories(orderbook PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})