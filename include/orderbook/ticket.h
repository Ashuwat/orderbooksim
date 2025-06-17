#include <cstdint>
class Ticket { 
    private:
        float limit;
        bool buySell;
        bool orderType; //true = limit, false = marketorder;
        std::uint16_t datetime;
        uint64_t trader_id;
    public:
        Ticket(
            float price,
            bool buySell, 
            bool OrderType,
            uint16_t datetime, 
            uint64_t trader_id);
};