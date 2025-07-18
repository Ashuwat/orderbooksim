#pragma once

#include <iostream>
#include <queue>
#include <memory>
#include <vector>
#include "../orderbook/ticket.h"
#include "latentTicket.h"

struct CompareLatencyToTrade {
    bool operator()(const LatentTicket& a, const LatentTicket& b) {
        return a.date > b.date; 
    }
};



class Latency {
    private:
        int latencyTrade;
        std::priority_queue<LatentTicket, std::vector<LatentTicket>, CompareLatencyToTrade> latencyToTrade;
     
    public:
        Latency();
        void setLatency(int number);
        void addTicket(const Ticket& ticket);
        Ticket retrieveArrivals(int time);
                
};

