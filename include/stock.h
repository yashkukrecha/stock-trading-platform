#ifndef STOCK_H
#define STOCK_H

#include "utils.h"

using namespace std;

class Stock {
    private:
        string symbol;
        string name;
        float price;
        vector<float> price_history;
    
    public:
        Stock (const string &symbol, const string &name, float initial_price);

        void brownian_motion ();
        void print_stock () const;

        // GETTERS
        string get_symbol ();
        string get_name ();
        float get_price ();
        vector<float> get_price_history ();
};

#endif // STOCK_H