#include "../../include/orderbook/bid.h"
#include <cstdint>
#include <memory>

Bid::Bid() : bidList(std::priority_queue<
    std::unique_ptr<Ticket>, 
    std::vector<std::unique_ptr<Ticket>>,
    BidTicketComparator>()) {};

void Bid::add(std::unique_ptr<Ticket> ticket) {
    bidList.push(std::move(ticket)); 
};

Ticket* Bid::getHighestBid() {
    if (bidList.empty()) {
        return nullptr;
    }
    return bidList.top().get();
};

void Bid::remove() {
    bidList.pop();
};

void Bid::editHighestBid(uint16_t shares) {
    Ticket* someTicket {bidList.top().get()};
    if (!someTicket) {return;}
    someTicket->editShares(shares);
};

