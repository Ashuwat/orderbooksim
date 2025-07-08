#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include "ask.h"
#include "bid.h"
#include "ticket.h"
#include "tradeRecord.h"
#include "ohlcv.h"
#include "../latency/latency.h"

class Ledger {
    private: 
        Ask ask;
        Bid bid; 
        Latency latencyObj;
        float startingPrice;
        float lastTradedPrice = startingPrice;
        std::vector<TradeRecord> log = {}; 

        void removeOpposingTicket(Ticket* ticket);
        void logTrade(
            float price,
            uint16_t quantity, 
            int timestamp);
        bool updateTraders(Ticket* initTicket, Ticket* topTicket);
        bool marketOrder(Ticket* ticket);
        bool limitOrder(Ticket* ticket);
        bool checkLedger(Ticket* ticket);
        void buy(Ticket ticket);
        void sell(Ticket ticket);
        void hold(Ticket ticket);
        void setStartingPrice(float startingPrice);

        public: 
        OHCVL returnOHCVL(int ticketEpochs, int count);
        void retrieveAllData(std::string seed);
        float getlatestTrade(int latency, int polling) const;
        void runEngine(int time);
        void trade(Ticket ticket);
        Ledger(float startingPrice, int latency);
};
