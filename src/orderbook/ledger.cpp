#include "../../include/orderbook/ledger.h"
#include "../../include/traders/traders.h"
#include "../../include/orderbook/tradeRecord.h"
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>

Ledger::Ledger() : bid(), ask() {};

void Ledger::logTrade(float price, uint16_t quantity, int timestamp) {
    lastTradedPrice = price;
    std::cout << timestamp << "\n";
    if (log.empty()) {
        log.emplace_back(price, quantity, timestamp);
    } else if (log.back().timestamp == timestamp) {
        log.back().price = price;
        log.back().quantity += quantity;
    } else {
        log.emplace_back(price, quantity, timestamp);
    }
};

OHCVL Ledger::returnOHCVL(int ticketEpochs) {
    int size = static_cast<int>(log.size());
    if (size == 0) {
        std::cout << "no trades in ohlcv log";
        return OHCVL(startingPrice, startingPrice, startingPrice, startingPrice, 0);
    } else if (log.back().timestamp == ticketEpochs) {
        return OHCVL(log.back().price, log.back().price, log.back().price, log.back().price, 0);
    }

    auto reverse = log.rbegin();
    float open = (reverse + ticketEpochs)->price;
    float high = reverse->price; 
    float low = reverse->price;
    float close = log.back().price;
    int volume = 0;
    for (auto itr = reverse; itr->timestamp != reverse->timestamp; ++itr) {
        if (itr->price > high) {high = itr->price;} 
        else if (itr->price < low) {low = itr->price;}
        volume += itr->quantity;
    }
    
    return (OHCVL(open, high, low, close, volume));
}

void Ledger::setStartingPrice(float price) {
    startingPrice = price;
}; 

float Ledger::getlatestTrade() const {
    if (log.empty()) {return startingPrice;}
    return log.back().price;
}

void Ledger::retrieveAllData() {
    std::ofstream outFile("marketData.csv");
    if(!outFile.is_open()) {std::cout << "error opening file"; return;}
    for (TradeRecord record : log) {
        outFile << record.price << "\n"; 
    }
};

void Ledger::hold(std::unique_ptr<Ticket> ticket) {
    if (log.empty()) {
        logTrade(startingPrice, 0, ticket->getDatetime());
    } else {
        logTrade(log.back().price, 0, ticket->getDatetime());
    }
}

void Ledger::buy(std::unique_ptr<Ticket> ticket) {
    if (checkLedger(ticket.get())) {
       bid.add(std::move(ticket)); 
    }
};

void Ledger::sell(std::unique_ptr<Ticket> ticket) {
    if (checkLedger(ticket.get())) {
        ask.add(std::move(ticket));
    }
};

void Ledger::removeOpposingTicket(Ticket* ticket) { //buy is true, ask is false
    if (ticket->getTypeOfBuy()) {
        ask.remove(); 
    } else {
        bid.remove();
    }
}

// void Ledger::updateTraders(Ticket* initTicket, Ticket* topTicket) {
//     float amountTransacted;
//     uint16_t sharesTransacted;
//     Trader* initTrader = initTicket->getTraderId(); 
//     Trader* opposingTrader = topTicket->getTraderId();
//     if (initTicket->getTypeOfBuy()) {
//         if (initTicket->getShares() < topTicket->getShares()) {
//             amountTransacted = initTicket->getShares() * topTicket->getLimit(); 
//             sharesTransacted = initTicket->getShares();
//             logTrade(topTicket->getLimit(), initTicket->getShares(), initTicket->getDatetime());
//         } else {
//             amountTransacted = topTicket->getShares() * topTicket->getLimit();
//             sharesTransacted = topTicket->getShares();
//             logTrade(topTicket->getLimit(), topTicket->getShares(), initTicket->getDatetime());
//         }

//         initTrader->editInvestment(amountTransacted * -1);
//         initTrader->editShares(sharesTransacted);
//         opposingTrader->editInvestment(amountTransacted);
//         opposingTrader->editShares(sharesTransacted * -1);
//     } else {
//         if (initTicket -> getShares() < topTicket -> getShares()) {
//             sharesTransacted = initTicket->getShares();
//             amountTransacted = initTicket->getShares() * topTicket->getLimit(); 
//             logTrade(topTicket->getLimit(), initTicket->getShares(), initTicket->getDatetime());
//         } else {
//             sharesTransacted = topTicket->getShares();
//             amountTransacted = topTicket->getShares() * topTicket->getLimit();
//             logTrade(topTicket->getLimit(), topTicket->getShares(), topTicket->getDatetime());
//         }
//         initTrader->editShares(sharesTransacted * -1);
//         initTrader->editInvestment(amountTransacted);
//         opposingTrader->editShares(sharesTransacted);
//         opposingTrader->editInvestment(amountTransacted * -1);
//     }
// }


bool Ledger::updateTraders(Ticket* initTicket, Ticket* topTicket) {
    Trader* buyer = initTicket->getTypeOfBuy() ? initTicket->getTraderId() : topTicket->getTraderId();
    Trader* seller = initTicket->getTypeOfBuy() ? topTicket->getTraderId() : initTicket->getTraderId();

    Ticket* buyTicket = initTicket->getTypeOfBuy() ? initTicket : topTicket;
    Ticket* sellTicket = initTicket->getTypeOfBuy() ? topTicket : initTicket;

    uint16_t sharesTransacted = std::min(buyTicket->getShares(), sellTicket->getShares());
    float amountTransacted = sharesTransacted * topTicket->getLimit();

    if (buyer->getInvestment() < amountTransacted || seller->getShares() < sharesTransacted) {
        std::cerr << "Invalid transaction - " << topTicket->getTraderId() << '\n';
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
    std::cout << "market\n";
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
    std::cout << "limit\n"; 
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