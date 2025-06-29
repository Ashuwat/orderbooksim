#pragma once

#include <cstdint>
#include <memory>

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
            int datetime, 
            Trader* trader);
        float getLimit() const;
        int getDatetime() const;
        void editShares(int shares);
        uint16_t getShares() const;
        bool getTypeOfBuy() const;
        Trader* getTraderId() const;
        bool getTypeOfOrder() const; // market is true, limit is false
        bool isTicketValid() const;
};


struct BidTicketComparator {
    bool operator()(const std::unique_ptr<Ticket>& a, const std::unique_ptr<Ticket>& b) const {
        if (a->getLimit() == b->getLimit()) {
            return a->getDatetime() > b->getDatetime(); // earlier = higher priority
        }
        return a->getLimit() < b->getLimit(); // higher price = higher priority
    }
};

struct AskTicketComparator {
    bool operator()(const std::unique_ptr<Ticket>& a, const std::unique_ptr<Ticket>& b) const {
        if (a->getLimit() == b->getLimit()) {
            return a->getDatetime() > b->getDatetime(); // earlier = higher priority
        }
        return a->getLimit() > b->getLimit(); // lower price = higher priority
    }
};
