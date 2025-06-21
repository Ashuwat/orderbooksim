#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
#include "ticket.h"

#pragma once

class Ask {
    private: 
    std::priority_queue<Ticket*, std::vector<Ticket*>, AskTicketComparator> askList; 

    public:
    Ask();
    void add(Ticket* ticket);
    Ticket* getLowestAsk();
    void remove();
    void editLowestAsk(uint16_t shares);
    int size();
}; 