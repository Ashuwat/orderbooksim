#include "../../include/orderbook/ohlcv.h"

OHCVL::OHCVL(
    float o,
    float h,
    float c,
    float l,
    int v) : open(o), high(h), close(c), low(l), volume(v) {}