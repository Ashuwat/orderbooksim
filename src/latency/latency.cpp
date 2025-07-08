#include "../../include/latency/latency.h"
#include "../../include/latency/latentTicket.h"

Latency::Latency() {latencyToTrade = {};}

void Latency::addTicket(const Ticket& ticket) {
    LatentTicket latTicket = LatentTicket(
            ticket, 
            ticket.getDatetime() + latencyTrade);  
    latencyToTrade.push(std::move(latTicket));
}

Ticket Latency::retrieveArrivals(int date) {
    if (latencyToTrade.empty()) {return Ticket{0,0,0,0,date,0};}
    const LatentTicket& topTick = latencyToTrade.top();
    if (topTick.date > date) {return Ticket{0,0,0,0,date,0};}
    Ticket ticketCopy = topTick.ticket;
    latencyToTrade.pop();
    return ticketCopy;
};

void Latency::setLatency(int number) {
    latencyTrade = number;
}