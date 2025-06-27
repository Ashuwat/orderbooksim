#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <random> 
#include <iostream>
#include "../../include/orderbook/ledger.h"
#include "../graph/info.h"
#include "../simulationContext.h"
#include "traderType.h"
#pragma once


class Trader {
    protected:
    TraderType traderType;
    SimulationContext& simCtx;
    float investment;
    int shares; 
    float tradingFreq;
    uint64_t trader_id;
    
    public:
    Trader(float inv, int share, SimulationContext& simCtx); 
    virtual ~Trader() = default;
    virtual void trade(
        Info& info,
        uint16_t time,
        Ledger& ledger
    ) = 0;
    int getShares();
    float getInvestment();
    void editShares(int sharesAmount);
    void editInvestment(float investmentAmount);
    void profile(); //stats about the trader
    uint64_t getAddress();
};