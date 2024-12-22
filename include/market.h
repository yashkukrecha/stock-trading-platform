#ifndef MARKET_H
#define MARKET_H

#include "utils.h"
#include "stock.h"
#include "orderbook.h"
#include "trader.h"

enum class TraderAction {
    BUY_ORDER,
    SELL_ORDER,
    GET_STOCKS
};

using namespace std;

class Market {
    private:
        vector<pair<Stock, OrderBook>> market;
        unordered_map<int, Trader> traders;

    public:
        void add_stock (Stock& stock);
        void print_market () const;

        void add_trader (int socket_desc, float initial_balance);

        // GETTERS
        vector<pair<Stock, OrderBook>> get_market ();
        string get_trader_info (int socket_desc);
};

#endif // MARKET_H