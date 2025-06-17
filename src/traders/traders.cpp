#include "../../include/trader/traders.h"
#include <random>

Trader::Trader (
    int inv, int share, SimulationContext simCtx) {
    investment = inv;
    shares = share;
    tradingFreq = simCtx.uniform_dist(simCtx.rng); 
    trader_id = simCtx.uniform_dist(simCtx.rng); 
};