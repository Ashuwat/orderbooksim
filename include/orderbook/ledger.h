#include <cstdint>
#include <iostream>
#include <vector>
#include "ask.h"
#include "bid.h"
#include "ticket.h"
#include "tradeRecord.h"
#pragma once

class Ledger {
    private: 
        Ask ask;
        Bid bid; 
        float lastTradedPrice;
        std::vector<TradeRecord> log; 
        
        void removeOpposingTicket(Ticket* ticket);
        void logTrade(
            float price,
            uint16_t quantity, 
            int timestamp);
        void updateTraders(Ticket* initTicket, Ticket* topTicket);
        bool marketOrder(Ticket* ticket);
        bool limitOrder(Ticket* ticket);
        bool checkLedger(Ticket* ticket);
    public: 
        void buy(Ticket* ticket);
        void sell(Ticket* ticket);
        Ledger();
};
