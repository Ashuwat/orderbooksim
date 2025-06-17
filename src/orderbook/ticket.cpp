#include "../../include/orderbook/ticket.h"

Ticket::Ticket(
    float limit,
    bool buySell,
    bool orderType, //true = limit, false = marketorder;
    std::uint16_t datetime,
    uint64_t trader_id
) : limit(limit), 
    buySell(buySell), 
    orderType(orderType), 
    datetime(datetime), 
    trader_id(trader_id) {
    
}