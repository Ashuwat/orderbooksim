#include "../traders.h"

class NoisyTrader : public Trader {
    public:
    using Trader::Trader;

    Ticket trade( 
        Info info,
        uint16_t time,
        float& strike_price, 
        Ledger& ledger,
        SimulationContext simCtx
    ) override {
        bool buyOrSell {simCtx.coin_flip(simCtx.rng)};
        float price {simCtx.norm_dist(simCtx.rng)};
        int quantity {simCtx.uniform_dist(simCtx.rng)};
        float afford {quantity * price};

        if (buyOrSell) { 
            if (afford <= investment) {
                return Ticket(
                    price, 
                    buyOrSell,
                    true,
                    time,
                    trader_id
                );
            };
        } else {
            if (quantity <= shares) {
                return Ticket(
                    price,
                    buyOrSell,
                    false,
                    time,
                    trader_id 
                );
            }    
        }
        return Ticket(0,0,0,0,0);
    }
};