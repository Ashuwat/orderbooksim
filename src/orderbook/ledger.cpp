#include "../../include/orderbook/ledger.h"
#include "../../include/traders/traders.h"
#include "../../include/orderbook/tradeRecord.h"
#include <cstdint>

Ledger::Ledger() : bid(), ask() {};

void Ledger::logTrade(float price, uint16_t quantity, int timestamp) {
    log.push_back(TradeRecord(
        price,
        quantity,
        timestamp
    ));
};

void Ledger::buy(Ticket* ticket) {
    if (!checkLedger(ticket)) {
       bid.add(ticket); 
    }
};

void Ledger::sell(Ticket* ticket) {
    if (!checkLedger(ticket)) {
        ask.add(ticket);
    }
};

void Ledger::removeOpposingTicket(Ticket* ticket) { //buy is true, ask is false
    if (ticket->getTypeOfBuy()) {
        ask.remove(); 
    } else {
        bid.remove();
    }
}

void Ledger::updateTraders(Ticket* initTicket, Ticket* topTicket) {
    float amountTransacted;
    uint16_t sharesTransacted;
    Trader* initTrader = initTicket->getTraderId(); 
    Trader* opposingTrader = topTicket->getTraderId();
    if (initTicket->getTypeOfBuy()) {
        if (initTicket->getShares() < topTicket->getShares()) {
            amountTransacted = initTicket->getShares() * topTicket->getLimit(); 
            sharesTransacted = initTicket->getShares();
        } else {
            amountTransacted = topTicket->getShares() * topTicket->getLimit();
            sharesTransacted = topTicket->getShares();
        }

        initTrader->editInvestment(amountTransacted * -1);
        initTrader->editShares(sharesTransacted);
        opposingTrader->editInvestment(amountTransacted);
        opposingTrader->editShares(sharesTransacted * -1);
    } else {
        if (initTicket -> getShares() < topTicket -> getShares()) {
            sharesTransacted = initTicket->getShares();
            amountTransacted = initTicket->getShares() * topTicket->getLimit(); 
        } else {
            sharesTransacted = topTicket->getShares();
            amountTransacted = topTicket->getShares() * topTicket->getLimit();
        }
        initTrader->editShares(sharesTransacted * -1);
        initTrader->editInvestment(amountTransacted);
        opposingTrader->editShares(sharesTransacted);
        opposingTrader->editInvestment(amountTransacted * -1);
    }
}

bool Ledger::marketOrder(Ticket* ticket) {
    Ticket* topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
    if (!topTicket) return true;
    while (ticket->getShares() != 0) {
        if (ticket->getShares() > topTicket->getShares()) {
            updateTraders(ticket,topTicket);
            ticket->editShares(ticket->getShares()-topTicket->getShares());
            removeOpposingTicket(ticket);
        } else if (ticket->getShares() == topTicket ->getShares()) {
            updateTraders(ticket,topTicket);
            removeOpposingTicket(ticket);
            return false; // don't add to the ask or bid
        } else {
            updateTraders(ticket,topTicket);
            topTicket->editShares(topTicket->getShares()-ticket->getShares());             
            return false;
        }
        
        topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
        if (!topTicket) break;
    } 
    return true; // add to ask or bid;
}

bool Ledger::limitOrder(Ticket* ticket) {
    Ticket* topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
    if (!topTicket) return true;
    bool priceIsAcceptable = ticket->getTypeOfBuy() ? ticket->getLimit() >= topTicket->getLimit() : ticket->getLimit() <= topTicket->getLimit(); 
    
    while (ticket -> getShares() != 0 && priceIsAcceptable) {
        if (ticket->getShares() > topTicket->getShares()) {
            updateTraders(ticket, topTicket); 
            ticket->editShares(ticket->getShares()-topTicket->getShares());
            removeOpposingTicket(ticket); 
        } else if (ticket->getShares() == topTicket ->getShares()) {
            updateTraders(ticket, topTicket);
            removeOpposingTicket(ticket);
            return false;
        } else {
            updateTraders(ticket, topTicket);
            topTicket->editShares(topTicket->getShares()-ticket->getShares());             
            return false;
        }
        
        topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
        if (!topTicket) break; 
        priceIsAcceptable = ticket->getTypeOfBuy() ? ticket->getLimit() >= topTicket->getLimit() : ticket->getLimit() <= topTicket->getLimit(); 
    }
    return true;
}

bool Ledger::checkLedger(Ticket* ticket) {
    if (ticket->getTypeOfBuy()) {
        Ticket* topTicket = ask.getLowestAsk();
        if (!topTicket) return true;
        
        if (topTicket->getTypeOfOrder()) {
            return marketOrder(ticket);
        } else {
            return limitOrder(ticket);
        }
    } else {
        Ticket* topTicket = bid.getHighestBid();
        if (!topTicket) return true;
        if (topTicket->getTypeOfOrder()) {
            return marketOrder(ticket);
        } else {
            return limitOrder(ticket);
        }
    }
};