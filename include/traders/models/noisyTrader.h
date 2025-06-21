#include "../traders.h"
#pragma once
class NoisyTrader : public Trader {
    private:
    Ticket ticketGeneration(
        Info& info,
        uint16_t time,
        Ledger& ledger,
        SimulationContext& simCtx
    );
    public:
    void trade(
        Info& info,
        uint16_t time,
        Ledger& ledger,
        SimulationContext& simCtx
    ) override;
    NoisyTrader(int inv, int share, SimulationContext& simCt);
};