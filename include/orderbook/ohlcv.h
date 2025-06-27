#pragma once

struct OHCVL {
    float open = 0;
    float high = 0;
    float low = 0; 
    float close = 0;
    int volume = 0;

    OHCVL(
        float o,
        float h,
        float l,
        float c,
        int v
    );
};