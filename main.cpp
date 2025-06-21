#include "src/traders/models/noisyTrader.cpp"
#include "src/orderbook/ledger.cpp"
#include "src/traders/traders.cpp"

Info generateInfo(int i) {
    if (i == 25) {
        return Info();
    } else {
        return Info();
    } 
}

int main() {
    // parameters
    const int numNoisy = 10000;
    // const int numRisk = 10000;
    // const int numEvent = 10000;
    // const int numInstitute = 10000;
    const int SIMULATION_EPOCHS {50};
    Ledger ledger {Ledger()};
    // SimulationContext simCtx {SimulationContext()};

    // std::array<std::unique_ptr<NoisyTrader>, numNoisy> noisyTraders;
    
    // for (int i = 0; i < 10000; i++) {
    //     noisyTraders[i] = std::make_unique<NoisyTrader>(100, 100, simCtx);
    // };

    // for (int i = 0; i < SIMULATION_EPOCHS; i++) {
    //     int randomTraderIndex {simCtx.uniform_dist(simCtx.rng)};
    //     randomTraderIndex = randomTraderIndex % numNoisy;
    //     Info info {generateInfo(i)};
    //     NoisyTrader& randomTrader {*noisyTraders[randomTraderIndex]};
    //     randomTrader.trade(info, i, ledger, simCtx);
    // };
 
    // has to have a struct to make the node list. 
    // randomly select a trader in the list.
    // there will be a list of randomly assigned traders 
    // then they trade like they are supposed to with their trading frequencies
    // - the institutions (higher ones have a default of low until info arrives)
    // if the trading frequency is higher than what it is supposed to (lets say 0.3)
    // then they trade, and they make something happen in the market
    // one simulation epoch would be going through all of the traders for one time step
    //
    // information is null, until it isn't (through a information object)
    // it get's passed to all the institutions first
    // there will be a graph based DS that connects all the traders
    // they will all get the information at one point and you can see how it affects the market
    //
    // the graph will be a weird connection of edges between many traders
    // there will be a heirarchy of course, there can only be few connections for each trader
    // the way it works is if the trader has a high info factor, then it spreads 
    // 
    // it can also be that the data structure itself has a method to distribute all the information
    // I'm not sure which one but could be the case and then you can just call it. 
};
