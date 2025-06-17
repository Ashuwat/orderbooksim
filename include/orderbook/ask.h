#include <iostream>
#include <queue>
#include <vector>
class Ask {
    private: 
    std::priority_queue<float, std::vector<float>, std::greater<float>> askList {};
    public:
    void add(float askNumber);
    float getLowestAsk();
}; 