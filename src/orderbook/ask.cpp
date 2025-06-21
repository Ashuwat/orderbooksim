#include "../../include/orderbook/ask.h"
#include <cstdint>

Ask::Ask() :
    askList(std::priority_queue<Ticket*, std::vector<Ticket*>, AskTicketComparator>()) {};

void Ask::add(Ticket* ticket) {
    askList.push(ticket); 
};

Ticket* Ask::getLowestAsk() {
    return askList.top();
};

void Ask::remove() {
    askList.pop();
};

void Ask::editLowestAsk(uint16_t shares) {
    Ticket* someTicket {askList.top()};
    someTicket->editShares(shares);
};

int Ask::size() {
    return askList.size();
}