#ifndef ORDER_H
#define ORDER_H

#include "utils.h"

using namespace std;

enum class OrderType {
    BUY,
    SELL
};

class Order {
    private:
        int trader_id;
        int quantity;
        float price;
        OrderType order_type;
        chrono::time_point<chrono::system_clock> timestamp;

    public:
        Order (int trader_id, int quantity, float price, OrderType order_type);

        bool reduce_quantity (int amount);
        bool operator < (const Order& other) const;
        bool operator > (const Order& other) const;

        // GETTERS
        int get_quantity ();
        OrderType get_order_type ();
};

#endif // ORDER_H