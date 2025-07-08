#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include "ticket.h"

class Ask {
    private: 
    std::priority_queue<
        std::unique_ptr<Ticket>, 
        std::vector<std::unique_ptr<Ticket>>,
        AskTicketComparator> askList; 

    public:
    Ask();
    void add(std::unique_ptr<Ticket> ticket);
    Ticket* getLowestAsk();
    void remove();
    void editLowestAsk(uint16_t shares);
}; 