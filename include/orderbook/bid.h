#include <iostream>
#include <queue>
#include <vector>

class Bid {
    private:
    std::priority_queue<float> bidlist {};
    public:
    void add();
    void remove();
    float getHighestBid();
    void editHighestBid();
};