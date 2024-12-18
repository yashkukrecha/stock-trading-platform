#include "order.h"

using namespace std;

Order::Order (int trader_id, int quantity, float price, OrderType order_type):
    trader_id(trader_id),
    quantity(quantity),
    price(price),
    order_type(order_type),
    timestamp(chrono::system_clock::now())
    {}

bool Order::reduce_quantity (int amount) {
    if (amount >= 0 && amount <= quantity) {
        quantity -= amount;
        return quantity == 0;
    }

    throw out_of_range("Amount out of range.");
}

bool Order::operator < (const Order& other) const {
    if (order_type == OrderType::BUY) {
        return (price < other.price) || (price == other.price && timestamp > other.timestamp);
    }
    return (price > other.price) || (price == other.price && timestamp > other.timestamp);
}

bool Order::operator > (const Order& other) const {
    return !(*this < other);
}

int Order::get_quantity () {
    return quantity;
}

OrderType Order::get_order_type () {
    return order_type;
}
