#include "../../include/orderbook/bid.h"
#include <cstdint>

Bid::Bid() : bidList(std::priority_queue<Ticket*, std::vector<Ticket*>, BidTicketComparator>()) {};

void Bid::add(Ticket* ticket) {
    bidList.push(ticket); 
};

Ticket* Bid::getHighestBid() {
    return bidList.top();
};

void Bid::remove() {
    bidList.pop();
};

void Bid::editHighestBid(uint16_t shares) {
    Ticket* someTicket {bidList.top()};
    someTicket->editShares(shares);
};

int Bid::size() {
    return bidList.size();
};