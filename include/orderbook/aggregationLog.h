#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "ohlcv.h"

class AggregationLog {
    private:
    std::vector<OHCVL> log;
    public:
    AggregationLog(int epochs);
    void add(OHCVL ohlcv);
    void retrieveAllData();
};