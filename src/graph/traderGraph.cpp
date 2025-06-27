#include "../../include/graph/traderNetwork.h"
#include <cstdint>
#include <vector>

TraderNetwork::TraderNetwork() {};

uint64_t TraderNetwork::sampleNeighbor(TraderType type, uint64_t id) {return -0;};

int TraderNetwork::sampleDegree(TraderType type) {return 0;};

void TraderNetwork::addTrader(Trader* trader) {
    traderList[trader->getAddress()] = trader;
};

void TraderNetwork::generateGraph() {};

void TraderNetwork::seedInformation(std::vector<uint64_t>& sources) {};

void TraderNetwork::propagateInfoICM(float& transmissionRate) {};

bool TraderNetwork::doesTraderHaveInfo(Trader* trader) const {return false;};