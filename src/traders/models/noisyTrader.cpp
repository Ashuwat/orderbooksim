#include "../../../include/traders/models/noisyTrader.h"
#include <algorithm>
#include <cstdint>
#include <random>

NoisyTrader::NoisyTrader(float inv, int share, SimulationContext& simCtx) 
    : Trader(inv, share, simCtx) {
    NoisyTrader::traderType = TraderType::Noisy; 
};

Ticket NoisyTrader::ticketGeneration(
    uint16_t time,
    Ledger& ledger
) {
    bool buyOrSell {simCtx.coin_flip(simCtx.rng)}; // buy means true, sell means false
    int latencyAmount = static_cast<int>(simCtx.norm_dist(simCtx.rng) * 1e4 + 1e5);
    float price {(simCtx.norm_dist(simCtx.rng)) / 30 + ledger.getlatestTrade(latencyAmount, static_cast<int>(1e6))};   
    price = std::max(0.0001f, price);
    int quantity {simCtx.uniform_dist(simCtx.rng) % 10 + 1};
    bool marketLimit {std::bernoulli_distribution(0.7)(simCtx.rng)};
    float afford {quantity * price};
   
    if (buyOrSell) { // buy      
        if (afford <= investment) {
            return Ticket(
                price, 
                quantity,
                buyOrSell,
                marketLimit, //false means limit, true means marketOrder
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
                marketLimit,
                time,
                this 
            );
        }    
    }
    return Ticket(0,0,0,0,time,0);
}

void NoisyTrader::trade(
    uint16_t time,
    Ledger& ledger
) {
    Ticket someTicket = ticketGeneration(time,ledger);
    ledger.trade(someTicket); 
    return;
}