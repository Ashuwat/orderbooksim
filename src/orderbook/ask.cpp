#include "../../include/orderbook/ask.h"
#include <cstdint>
#include <memory>

Ask::Ask() :
    askList(std::priority_queue<std::unique_ptr<Ticket>, 
            std::vector<std::unique_ptr<Ticket>>,
            AskTicketComparator>()) {};

void Ask::add(std::unique_ptr<Ticket> ticket) {
    askList.push(std::move(ticket)); 
};

Ticket* Ask::getLowestAsk() {
    if (askList.empty()) {
        return nullptr;
    }
    return askList.top().get();
};

void Ask::remove() {
    askList.pop();
};

void Ask::editLowestAsk(uint16_t shares) {
    Ticket* someTicket {askList.top().get()};
    if (!someTicket) {return;}
    someTicket->editShares(shares);
};