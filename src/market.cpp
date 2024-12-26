#include "market.h"

using namespace std;

void Market::add_stock (Stock& stock, int market_cap) {
    OrderBook ob(stock.get_symbol());

    // This initial order is what is available on the market
    Order initial_order(-1, market_cap, stock.get_price(), OrderType::SELL);
    ob.add_order(initial_order, *this);
    this->add_trader(-1, 0.0);

    market.push_back({stock, ob});
}

void Market::add_trader (int socket_desc, float initial_balance) {
    if (traders.find(socket_desc) == traders.end()) {
        Trader t(initial_balance);
        traders[socket_desc] = t;
    }
}

string Market::add_order (int socket_desc, string request) {
    if (traders.find(socket_desc) != traders.end()) {

        // split the string
        vector<string> result;
        result.reserve(2);
        int pos = 0;
        int next_pos;

        while ((next_pos = request.find(":", pos)) != string::npos) {
            result.push_back(request.substr(pos, next_pos - pos));
            pos = next_pos + 1;
        }

        if (result.size() != 2) {
            return "Invalid request";
        }


        int quantity = stoi(request.substr(pos));

        // check if stock exists
        if (market.empty()) {
            return "Stock does not exist";
        }

        pair<Stock, OrderBook>& p = market[0];
        for (auto stock : market) {
            if (stock.first.get_symbol() == result[1]) {
                p = stock;
                break;
            }
        }

        if (p.first.get_symbol() != result[1]) {
            return "Stock does not exist";
        }

        // check the trader
        Trader t = traders[socket_desc];
        if (result[0] == "BUY") {

            // trader does not have enough money for the transaction
            if (t.get_balance() < p.first.get_price() * quantity) {
                return "Not enough funds for buy request";
            }

            Order o(socket_desc, quantity, p.first.get_price(), OrderType::BUY);
            p.second.add_order(o, *this);
            return "Buy order added successfully";

        } else if (result[0] == "SELL") {

            // trader does not possess the stocks they wish to sell
            if (t.get_quantity(p.first.get_symbol()) < quantity) {
                return "Not enough assets for sell request";
            }

            Order o(socket_desc, quantity, p.first.get_price(), OrderType::SELL);
            p.second.add_order(o, *this);
            return "Sell order added successfully";

        } else {
            return "Invalid request";
        }
    }

    return "Trader does not exist";
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

Trader& Market::get_trader (int socket_desc) {
    if (traders.find(socket_desc) != traders.end()) {
        return traders[socket_desc];
    }
    throw runtime_error("Trader does not exist");
}

string Market::get_trader_info (int socket_desc) {
    if (traders.find(socket_desc) != traders.end()) {
        return traders[socket_desc].get_stocks();
    }
    return "No trader found";
}