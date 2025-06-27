#include "../../include/orderbook/aggregationLog.h"
#include <fstream>
#include <memory>

AggregationLog::AggregationLog(int epochs) {
    log.reserve(epochs);
}

void AggregationLog::add(OHCVL ohlcv) {
    log.emplace_back(std::move(ohlcv));
}

void AggregationLog::retrieveAllData() {
    std::ofstream outFile("ohcvl.csv");
    if(!outFile.is_open()) {std::cout << "error opening csv"; return;}
    for (OHCVL record : log) {
        outFile << record.open << "," << record.high << "," << record.low << "," << record.close << "," << record.volume << "\n";
    }
}