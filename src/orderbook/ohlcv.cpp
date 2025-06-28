#include "../../include/orderbook/ohlcv.h"

OHCVL::OHCVL(
    float o,
    float h,
    float l,
    float c,
    int v) : open(o), high(h), low(l), close(c), volume(v) {}