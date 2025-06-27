#include "../../include/orderbook/tradeRecord.h"
#include <cstdint>

TradeRecord::TradeRecord(float price, uint16_t quantity, int timestamp) :
price(price), quantity(quantity), timestamp(timestamp) {};