#include <cstdint>
#pragma once

struct TradeRecord {
    float price;
    uint16_t quantity;
    int timestamp;

    TradeRecord(
        float price,
        uint16_t quantity,
        int timestamp
    );
};