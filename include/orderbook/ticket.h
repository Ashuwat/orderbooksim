#include <cstdint>
#pragma once

class Trader;

class Ticket { 
    private:
        float limit;
        uint16_t shares;
        bool buySell;
        bool marketOrLimit;
        int datetime;
        Trader* trader_id;
    public:
       Ticket(
            float price,
            uint16_t shares,
            bool buySell,
            bool marketOrLimit,
            uint16_t datetime, 
            Trader* trader);
        float getLimit() const;
        uint16_t getDatetime() const;
        void editShares(uint16_t shares);
        uint16_t getShares() const;
        bool getTypeOfBuy() const;
        Trader* getTraderId() const;
        bool getTypeOfOrder() const; // market is true, limit is false
};


struct BidTicketComparator {
    bool operator()(const Ticket* a, const Ticket* b) const {
        if (a->getLimit() == b->getLimit()) {
            return a->getDatetime() > b->getDatetime(); // earlier = higher priority
        }
        return a->getLimit() < b->getLimit(); // higher price = higher priority
    }
};

struct AskTicketComparator {
    bool operator()(const Ticket* a, const Ticket* b) const {
        if (a->getLimit() == b->getLimit()) {
            return a->getDatetime() > b->getDatetime(); // earlier = higher priority
        }
        return a->getLimit() > b->getLimit(); // higher price = higher priority
    }
};
