#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <random> 
#include <iostream>
#include "../../include/orderbook/ledger.h"
#include "../info.h"
#include "../simulationContext.h"
#pragma once

class Trader {
    protected:
    int investment;
    int shares; 
    float tradingFreq;
    uint64_t trader_id;

    void marketOrder();
    void limitOrder();

    public:
    Trader(int inv, int share, SimulationContext simCtx); 
    virtual Ticket trade(
        Info info,
        uint16_t time,
        float& strike_price,
        Ledger& ledger,
        SimulationContext simCtx
    ) = 0;

    virtual ~Trader() = default;
    void profile(); //stats about the trader
};