#include "../../include/orderbook/aggregationLog.h"
#include <fstream>

AggregationLog::AggregationLog(int epochs) {
    log.reserve(epochs);
}

void AggregationLog::add(OHCVL ohlcv) {
    log.emplace_back(std::move(ohlcv));
}

void AggregationLog::retrieveAllData() {
    std::ofstream outFile("ohlcv.csv");
    if(!outFile.is_open()) {std::cout << "error opening csv"; return;}
    for (const OHCVL& record : log) {
        outFile << record.open << "," << record.high << "," << record.low << "," << record.close << "," << record.volume << "\n";
    }
}