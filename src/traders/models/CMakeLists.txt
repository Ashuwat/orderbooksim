add_library(
    noisyTrader.cpp
    institutionTrader.cpp
    riskTrader.cpp
    eventTrader.cpp
)

target_include_directories(models
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(models
    PUBLIC traders
)