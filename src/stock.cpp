#include "stock.h"

using namespace std;

Stock::Stock (const string &symbol, const string &name, float initial_price):
    symbol(symbol),
    name(name),
    price(initial_price)
    {
        price_history.push_back(initial_price);
    }

void Stock::brownian_motion () {
    float change = (rand() % 100 - 50) / 100.0f;
    // price cannot drop to negative values
    while (price + change < 0) {
        change = (rand() % 100 - 50) / 100.0f;
    }
    price = price + change;
    price_history.push_back(price);
}

void Stock::print_stock () const {
    cout << "Stock: " << name << " (" << symbol << ")\n";
    cout << "Current Price: $" << price << "\n";
    cout << "Price History: ";
    for (float prices : price_history) {
        cout << "$" << prices << ", ";
    }
    cout << endl; 
}

string Stock::get_symbol () {
    return symbol;
}

string Stock::get_name () {
    return name;
}

float Stock::get_price () {
    return price;
}

vector<float> Stock::get_price_history () {
    return price_history;
}