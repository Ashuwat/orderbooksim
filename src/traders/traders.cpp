#include "../../include/traders/traders.h"
#include <cstdint>
#include <random>

Trader::Trader (
    float inv, int share, SimulationContext& _simctx) : simCtx(_simctx) {
    investment = inv;
    shares = share;
    tradingFreq = 0.5; 
    trader_id = simCtx.uniform_dist(simCtx.rng);
}

int Trader::getShares() {return shares;}
float Trader::getInvestment() {return investment;}

void Trader::editShares(int sharesAmount) {
    shares = shares + sharesAmount;
}

void Trader::editInvestment(float investmentAmount) {
    investment = investment + investmentAmount;
} 

void Trader::profile() {
    std::cout << "INVESTMENT: " << investment << '\n';
    std::cout << "SHARES: " << shares << '\n';
    std::cout << "----\n";
}

uint64_t Trader::getAddress() {return trader_id;}