#include "../../include/orderbook/ticket.h"
#include <cstdint>

Ticket::Ticket(
    float price,
    uint16_t shares,
    bool buySell,
    bool marketOrLimit,
    int datetime, 
    Trader* trader) :   
    limit(price), 
    shares(shares),
    buySell(buySell), 
    marketOrLimit(marketOrLimit),
    datetime(datetime),
    trader_id(trader) {};

float Ticket::getLimit() const {return limit;};

int Ticket::getDatetime() const {return datetime;};

void Ticket::editShares(int edit) {
    shares = shares + edit;
};

uint16_t Ticket::getShares() const {return shares;};

bool Ticket::getTypeOfBuy() const {return buySell;};

Trader* Ticket::getTraderId() const {return trader_id;};

bool Ticket::getTypeOfOrder() const {return marketOrLimit;};

bool Ticket::isTicketValid() const {
 if (trader_id == 0) {return false;}
 else return true;   
}