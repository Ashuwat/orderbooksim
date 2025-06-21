#include "../../../include/traders/models/noisyTrader.h"
#include <cstdint>

NoisyTrader::NoisyTrader(int inv, int share, SimulationContext& simCtx) 
    : Trader(inv, share, simCtx) {
    NoisyTrader::traderType = TraderType::Noisy; 
};

Ticket NoisyTrader::ticketGeneration(
    Info& info,
    uint16_t time,
    Ledger& ledger,
    SimulationContext& simCtx
) {
    bool buyOrSell {simCtx.coin_flip(simCtx.rng)};
    float price {simCtx.norm_dist(simCtx.rng)};
    int quantity {simCtx.uniform_dist(simCtx.rng)};
    float afford {quantity * price};

    if (buyOrSell) { // buy
        if (afford <= investment) {
            return Ticket(
                price, 
                quantity,
                buyOrSell,
                false, //false means limit, true means marketOrder
                time,
                this 
            );
        };
    } else { // sell
        if (quantity <= shares) {
            return Ticket(
                price,
                quantity,
                buyOrSell,
                false,
                time,
                this 
            );
        }    
    }
    return Ticket(0,0,0,0,0,0);
}

void NoisyTrader::trade(
    Info& info,
    uint16_t time,
    Ledger& ledger,
    SimulationContext& simCtx
) {
    Ticket someTicket = ticketGeneration(info,time,ledger,simCtx);
    if (someTicket.getTypeOfBuy()) {
        ledger.buy(&someTicket);
    } else {
        ledger.sell(&someTicket);
    }
    
}