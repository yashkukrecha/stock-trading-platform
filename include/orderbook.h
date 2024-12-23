#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "utils.h"
#include "order.h"

using namespace std;
class Market;

class OrderBook {
    private:
        string stock_symbol;

        // buy orders are from highest to lowest price, sell orders are lowest to highest
        priority_queue<Order> buy_orders;
        priority_queue<Order, vector<Order>, less<Order>> sell_orders;

    public:
        OrderBook (const string& stock_symbol);

        void add_order (const Order& order, Market& market);
        void match_orders (Market& market);
        pair<double, double> get_best_bid_ask () const;
        void print_order_book () const;
};


#endif // ORDERBOOK_H