#pragma once

#include "../traders.h"

class NoisyTrader : public Trader {
    private:
    Ticket ticketGeneration(
        Info& info,
        uint16_t time,
        Ledger& ledger
    );
    public:
    void trade(
        Info& info,
        uint16_t time,
        Ledger& ledger
    ) override;
    NoisyTrader(float inv, int share, SimulationContext& simCt);
};