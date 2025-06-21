#include "../../include/orderbook/ticket.h"

Ticket::Ticket(
    float price,
    uint16_t shares,
    bool buySell,
    bool marketOrLimit,
    uint16_t datetime, 
    Trader* trader) :   
    limit(price), 
    shares(shares),
    buySell(buySell), 
    marketOrLimit(marketOrLimit),
    datetime(datetime),
    trader_id(trader) {};
