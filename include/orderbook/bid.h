#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include "ticket.h"

class Bid {
    private:
    std::priority_queue<std::unique_ptr<Ticket>, std::vector<std::unique_ptr<Ticket>>, BidTicketComparator> bidList;

    public:
    Bid();
    void add(std::unique_ptr<Ticket> ticket);
    Ticket* getHighestBid();
    void remove();
    void editHighestBid(uint16_t shares);
};