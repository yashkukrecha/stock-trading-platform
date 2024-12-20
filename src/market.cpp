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

vector<pair<Stock, OrderBook>> Market::get_market () {
    return market;
}