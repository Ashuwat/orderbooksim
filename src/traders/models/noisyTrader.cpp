#include "../../../include/traders/models/noisyTrader.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <random>

NoisyTrader::NoisyTrader(float inv, int share, SimulationContext& simCtx) 
    : Trader(inv, share, simCtx) {
    NoisyTrader::traderType = TraderType::Noisy; 
};

Ticket NoisyTrader::ticketGeneration(
    Info& info,
    uint16_t time,
    Ledger& ledger
) {
    bool buyOrSell {simCtx.coin_flip(simCtx.rng)}; // buy means true, sell means false
    float price {(simCtx.norm_dist(simCtx.rng)) / 10 + ledger.getlatestTrade()};
    price = std::max(0.01f, price);
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
    return Ticket(0,0,0,0,0,0);
}

void NoisyTrader::trade(
    Info& info,
    uint16_t time,
    Ledger& ledger
) {
    std::unique_ptr<Ticket> someTicket = std::make_unique<Ticket>(ticketGeneration(info,time,ledger));
    if (someTicket->isTicketValid() == false) {
        ledger.hold(std::move(someTicket));
        return;
    }

    if (someTicket->getTypeOfBuy()) {
        ledger.buy(std::move(someTicket));
    } else {
        ledger.sell(std::move(someTicket));
    }    
}