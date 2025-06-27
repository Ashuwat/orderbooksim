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

class Ledger {
    private: 
        Ask ask;
        Bid bid; 
        float lastTradedPrice = startingPrice;
        std::vector<TradeRecord> log = {}; 
        float startingPrice;

        void removeOpposingTicket(Ticket* ticket);
        void logTrade(
            float price,
            uint16_t quantity, 
            int timestamp);
        bool updateTraders(Ticket* initTicket, Ticket* topTicket);
        bool marketOrder(Ticket* ticket);
        bool limitOrder(Ticket* ticket);
        bool checkLedger(Ticket* ticket);
    public: 
        OHCVL returnOHCVL(int ticketEpochs);
        void setStartingPrice(float startingPrice);
        void retrieveAllData();
        float getlatestTrade() const;
        void buy(std::unique_ptr<Ticket> ticket);
        void sell(std::unique_ptr<Ticket> ticket);
        void hold(std::unique_ptr<Ticket> ticket);
        Ledger();
};
