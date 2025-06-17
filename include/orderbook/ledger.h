#include <cstdint>
#include <iostream>
#include "ask.h"
#include "bid.h"
#include "ticket.h"

#pragma once

class Ledger {
    private: 
        Ask Ask;
        Bid Bid; 
    // bool validateOrder();
    // bool makeOrder();
    public: 
    // explicit Ledger();
    Ledger();
    void intake(uint64_t addr, Ticket ticket);
    void check();
};
