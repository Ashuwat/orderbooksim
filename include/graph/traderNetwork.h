#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include "../../include/traders/traders.h"
#pragma once

class TraderNetwork{
    private:
    std::unordered_map<uint64_t, Trader*> traderList;
    std::unordered_map<uint64_t, std::vector<uint64_t>> adjacencyGraph;
    std::unordered_map<uint64_t, bool> hasInformation;
    std::unordered_map<uint64_t, float> infoStrength;
    
    uint64_t sampleNeighbor(TraderType type, uint64_t id);
    int sampleDegree(TraderType type);

    public:
    TraderNetwork();
    void addTrader(Trader* trader);
    void generateGraph();
    void seedInformation(std::vector<uint64_t>& sources);
    void propagateInfoICM(float& transmissionRate);
    bool doesTraderHaveInfo(Trader* trader) const;
};