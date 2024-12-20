#ifndef MARKET_H
#define MARKET_H

#include "utils.h"
#include "stock.h"
#include "orderbook.h"

using namespace std;

class Market {
    private:
        vector<pair<Stock, OrderBook>> market;

    public:
        void add_stock (Stock& stock);
        void print_market () const;

        // GETTERS
        vector<pair<Stock, OrderBook>> get_market ();
};

#endif // MARKET_H