#include "market.h"

using namespace std;

void Market::add_stock (Stock& stock) {
    OrderBook ob(stock.get_symbol());
    market.push_back({stock, ob});
}

void Market::print_market () const {
    cout << "Market: \n";
    for (auto stock : market) {
        stock.second.print_order_book();
    }
}

void Market::add_trader (int socket_desc, float initial_balance) {
    if (traders.find(socket_desc) == traders.end()) {
        Trader t(initial_balance);
        traders[socket_desc] = t;
    }
}

vector<pair<Stock, OrderBook>> Market::get_market () {
    return market;
}

string Market::get_trader_info (int socket_desc) {
    if (traders.find(socket_desc) != traders.end()) {
        return traders[socket_desc].get_stocks();
    }
    return "No trader found";
}