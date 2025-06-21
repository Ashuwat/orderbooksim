#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
#include "ticket.h"

#pragma once

class Bid {
    private:
    std::priority_queue<Ticket*, std::vector<Ticket*>, BidTicketComparator> bidList;

    public:
    Bid();
    void add(Ticket* ticket);
    Ticket* getHighestBid();
    void remove();
    void editHighestBid(uint16_t shares);
    int size();
};