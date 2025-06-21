#include "../../include/traders/traders.h"
#include <cstdint>
#include <random>

Trader::Trader (
    int inv, int share, SimulationContext& simCtx) {
    investment = inv;
    shares = share;
    tradingFreq = simCtx.uniform_dist(simCtx.rng); 
    trader_id = simCtx.uniform_dist(simCtx.rng);
};

uint64_t Trader::getAddress() {
    return trader_id;
}