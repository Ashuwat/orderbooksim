#include "include/traders/models/noisyTrader.h"
#include "include/orderbook/ledger.h"
#include "include/traders/traders.h"
#include "include/orderbook/aggregationLog.h"
#include <memory>
#include <random>
#include <string>

int main(int argc, char*argv[]) {
    // for params
    unsigned int seed = std::random_device{}(); 

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "--seed") && i + 1 < argc) {
            seed = std::stoul(argv[++i]);
        }
    }

    std::cout << seed << '\n';  

    // parameters
    const long NUM_NOISY = 100000;
    // const int numRisk = 10000;
    // const int numEvent = 10000;
    // const int numInstitute = 10000;
    const long SIMULATION_EPOCHS = 1000000;
    int internalCount = 0;
    int count = 0;

    AggregationLog aggLog = AggregationLog(SIMULATION_EPOCHS);
    Ledger ledger {Ledger(20, 200)};
    SimulationContext simCtx {SimulationContext(seed)};
    

    std::array<std::unique_ptr<NoisyTrader>, NUM_NOISY> noisyTraders;
    
    for (int i = 0; i < NUM_NOISY; ++i) {
       noisyTraders[i] = std::make_unique<NoisyTrader>(10000.0f, 1000, simCtx);
    };


    for (int i = 0; i < SIMULATION_EPOCHS; ++i) {
        int randomVolumeGenerator = 10;
        for (int j = 0; j < randomVolumeGenerator; ++j) {
            bool randomChance {simCtx.uniform_dist(simCtx.rng) % 100 > 90};
            // std::cout << randomChance << '\n';
            if (randomChance) {
                int randomTraderIndex {simCtx.uniform_dist(simCtx.rng) % NUM_NOISY};
                NoisyTrader& randomTrader {*noisyTraders[randomTraderIndex]};
    
                // NoisyTraders trade on latency
                // HFTTraders trade basically on very very very low latency (last trade or second to last trade) & have some distribution
    
                randomTrader.trade(internalCount, ledger);
            }
            ++internalCount;
            ledger.runEngine(internalCount);
        }
        OHCVL hello = ledger.returnOHCVL(count, count + randomVolumeGenerator);
        aggLog.add(hello); 
        count += randomVolumeGenerator;
   }; 


    ledger.retrieveAllData(std::to_string(seed));
    aggLog.retrieveAllData();
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
