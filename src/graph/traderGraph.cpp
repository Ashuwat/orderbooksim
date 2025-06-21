#include "../../include/graph/traderNetwork.h"

void TraderNetwork::addTrader(Trader* trader) {
    traderList[trader->getAddress()] = trader;
};

