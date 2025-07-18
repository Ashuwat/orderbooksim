#include "../../include/latency/latency.h"
#include "../../include/orderbook/ledger.h"
#include "../../include/traders/traders.h"
#include "../../include/orderbook/tradeRecord.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>

Ledger::Ledger(float startingPrice, int latency) : 
    bid(), ask(), latencyObj(), startingPrice(startingPrice) {
    latencyObj.setLatency(latency);
};

void Ledger::logTrade(float price, uint16_t quantity, int timestamp) {
    lastTradedPrice = price;
    if (log.empty()) {
        log.emplace_back(price, quantity, timestamp);
    } else if (log.back().timestamp == timestamp) {
        log.back().price = price;
        log.back().quantity += quantity;
    } else {
        log.emplace_back(price, quantity, timestamp);
    }
};

OHCVL Ledger::returnOHCVL(int startIdx, int endIdx) {
    int size = static_cast<int>(log.size());

    if (startIdx >= size) return OHCVL(
            startingPrice, 
            startingPrice, 
            startingPrice,
            startingPrice,
            0);
    endIdx = std::min(endIdx, size);

    float open = log[startIdx].price;
    float high = log[startIdx].price;
    float low  = log[startIdx].price;
    float close = log[endIdx - 1].price;
    int volume = 0;

    for (int i = startIdx; i < endIdx; ++i) {
        if (log[i].price > high) high = log[i].price;
        if (log[i].price < low)  low = log[i].price;
        volume += log[i].quantity;
    }
    // std::cout << open << "," << high << "," << low << "," << close << "," << volume << "\n";
    return OHCVL(open, high, low, close, volume);
}


void Ledger::setStartingPrice(float price) {
    startingPrice = price;
}; 

float Ledger::getlatestTrade(int latency = 0, int polling = 1) const {
    if (log.empty()) {return startingPrice;}
    if (log.size() <= latency) {return startingPrice;} 
    size_t lastIndex = (log.size()) - latency - 1;
    int actualIndex = (static_cast<int>(lastIndex) / polling) * polling;
    return log[actualIndex].price;
}

void Ledger::retrieveAllData(std::string seed) {
    std::ofstream outFile("marketData" + seed + ".csv");
    if(!outFile.is_open()) {std::cout << "error opening file"; return;}
    for (TradeRecord record : log) {
        outFile << record.price << "\n"; 
    }
};

void Ledger::trade(Ticket ticket) { 
    latencyObj.addTicket(ticket);
}

void Ledger::runEngine(int time) {
    Ticket someTicket {latencyObj.retrieveArrivals(time)};
    if (!someTicket.isTicketValid()) {hold(someTicket); return;}
    if (someTicket.getTypeOfBuy()) {buy(someTicket); return;}
    else sell(someTicket); return;
}

void Ledger::hold(Ticket ticket) { 
    if (log.empty()) {
        logTrade(startingPrice, 0, ticket.getDatetime());
    } else {
        logTrade(log.back().price, 0, ticket.getDatetime());
    }
}

void Ledger::buy(Ticket ticket) {
    if (checkLedger(&ticket)) {
       std::unique_ptr<Ticket> tickUniq = std::make_unique<Ticket>(ticket);
       bid.add(std::move(tickUniq)); 
    }
};

void Ledger::sell(Ticket ticket) {
    if (checkLedger(&ticket)) {
        std::unique_ptr<Ticket> tickUniq = std::make_unique<Ticket>(ticket);
        ask.add(std::move(tickUniq));
    }
};

void Ledger::removeOpposingTicket(Ticket* ticket) { //buy is true, ask is false
    if (ticket->getTypeOfBuy()) {
        ask.remove(); 
    } else {
        bid.remove();
    }
}

bool Ledger::updateTraders(Ticket* initTicket, Ticket* topTicket) {
    Trader* buyer = initTicket->getTypeOfBuy() ? initTicket->getTraderId() : topTicket->getTraderId();
    Trader* seller = initTicket->getTypeOfBuy() ? topTicket->getTraderId() : initTicket->getTraderId();

    Ticket* buyTicket = initTicket->getTypeOfBuy() ? initTicket : topTicket;
    Ticket* sellTicket = initTicket->getTypeOfBuy() ? topTicket : initTicket;

    uint16_t sharesTransacted = std::min(buyTicket->getShares(), sellTicket->getShares());
    float amountTransacted = sharesTransacted * topTicket->getLimit();

    if (buyer->getInvestment() < amountTransacted || seller->getShares() < sharesTransacted) {
        if (!log.empty()) {
            logTrade(log.back().price, 0, initTicket->getDatetime());
        } else {
            logTrade(startingPrice, 0, initTicket->getDatetime());
        }
        return false;  
    }
    logTrade(topTicket->getLimit(), sharesTransacted, initTicket->getDatetime());

    buyer->editInvestment(-amountTransacted);
    buyer->editShares(sharesTransacted);

    seller->editInvestment(amountTransacted);
    seller->editShares(-sharesTransacted);

    return true;  
}

bool Ledger::marketOrder(Ticket* ticket) {
    Ticket* topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
    if (!topTicket) {
        if (!log.empty()) {
            logTrade(log.back().price, 0, ticket->getDatetime());
        } else {
            logTrade(startingPrice, 0, ticket->getDatetime());
        }
        return true;
    }
    while (ticket->getShares() != 0) {
        if (ticket->getShares() >= topTicket->getShares()) {
            if (!updateTraders(ticket,topTicket)) {
                removeOpposingTicket(ticket);
            } else if (ticket->getShares() == topTicket->getShares()) {
                removeOpposingTicket(ticket);
                return false;
            } else {
                ticket->editShares(ticket->getShares()-topTicket->getShares());
                removeOpposingTicket(ticket);     
            }
        } else {
            if (!updateTraders(ticket,topTicket)) {
                removeOpposingTicket(ticket);
            } else {
               topTicket->editShares(topTicket->getShares()-ticket->getShares());             
                return false; 
            }
        }
        topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
        if (!topTicket) break;
    } 
    return true; // add to ask or bid;
}

bool Ledger::limitOrder(Ticket* ticket) {
    Ticket* topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
    if (!topTicket) {
        if (!log.empty()) {
            logTrade(log.back().price, 0, ticket->getDatetime());
        } else {
            logTrade(startingPrice, 0, ticket->getDatetime());
        }
        return true;
    };
    bool priceIsAcceptable = ticket->getTypeOfBuy() ? ticket->getLimit() >= topTicket->getLimit() : ticket->getLimit() <= topTicket->getLimit(); 
    while (ticket -> getShares() != 0 || priceIsAcceptable) {
        if (ticket->getShares() >= topTicket->getShares()) {
            if (!updateTraders(ticket,topTicket)) {
                removeOpposingTicket(ticket);
            } else if (ticket->getShares() == topTicket->getShares()) {
                removeOpposingTicket(ticket);
                return false;
            } else {
                ticket->editShares(ticket->getShares()-topTicket->getShares());
                removeOpposingTicket(ticket);     
            }
        } else {
            if (!updateTraders(ticket,topTicket)) {
                removeOpposingTicket(ticket);
            } else {
                topTicket->editShares(topTicket->getShares()-ticket->getShares());             
                return false; 
            }
        }
        topTicket = ticket->getTypeOfBuy() ? ask.getLowestAsk() : bid.getHighestBid();
        if (!topTicket) break;
        bool priceIsAcceptable = ticket->getTypeOfBuy() ? ticket->getLimit() >= topTicket->getLimit() : ticket->getLimit() <= topTicket->getLimit();
        
    }
    return true;
}

bool Ledger::checkLedger(Ticket* ticket) {
    if (ticket->getTypeOfBuy()) { 
        if (ticket->getTypeOfOrder()) {
            return marketOrder(ticket);
        } else {
            return limitOrder(ticket);
        }
    } else {
        if (ticket->getTypeOfOrder()) {
            return marketOrder(ticket);
        } else {
            return limitOrder(ticket);
        }
    }
};