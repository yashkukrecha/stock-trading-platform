#include "market.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

// Test fixture for OrderBook tests
class OrderBookTest : public ::testing::Test {
protected:
    void SetUp() override {
        m = std::make_unique<Market>();
        Stock s("TSLA", "Tesla Inc.", 200.0);
        m->add_stock(s, 5000);
    }

    std::unique_ptr<Market> m;
};

// Test 1: Verify Constructor
TEST_F(OrderBookTest, ConstructorInitializesCorrectly) {
    const auto& market = m->get_market(); // Safely fetch a const reference
    const auto& ob = market.at(0).second; // Use `at` for bounds-checked access
    
    auto best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 0.0);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 200.0);
}

// Test 2: Verify Adding Order
TEST_F(OrderBookTest, AddOrder) {
    const auto& market = m->get_market();
    auto& ob = const_cast<OrderBook&>(market.at(0).second); 
    
    Order buy_order(1, 100, 25.6, OrderType::BUY);
    ob.add_order(buy_order, *m);

    auto best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 25.6);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 200.0);

    Order sell_order(1, 120, 32.4, OrderType::SELL);
    ob.add_order(sell_order, *m);

    best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 25.6);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 32.4);
}

// Test 3: Verify Matching Orders
TEST_F(OrderBookTest, MatchOrders) {
    const auto& market = m->get_market();
    auto& ob = const_cast<OrderBook&>(market.at(0).second);

    m->add_trader(1, 10000.0);
    m->add_trader(2, 10000.0);

    // Add buy order
    Order buy_order(1, 100, 25.6, OrderType::BUY);
    ob.add_order(buy_order, *m);
    auto best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 25.6);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 200.0);

    // Add sell order that does not match
    Order sell_order(2, 20, 32, OrderType::SELL);
    ob.add_order(sell_order, *m);
    best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 25.6);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 32.0);

    // Add sell order that matches
    Order match_sell_order(2, 120, 20, OrderType::SELL);
    ob.add_order(match_sell_order, *m);
    best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 0.0);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 20.0);
    EXPECT_FLOAT_EQ(m->get_trader(1).get_balance(), 8000.0);
    EXPECT_FLOAT_EQ(m->get_trader(2).get_balance(), 12000.0);

    // Add new buy order
    Order new_buy_order(1, 150, 76.4, OrderType::BUY);
    ob.add_order(new_buy_order, *m);
    best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 76.4);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 200.0);
    EXPECT_FLOAT_EQ(m->get_trader(1).get_balance(), 6960.0);
    EXPECT_FLOAT_EQ(m->get_trader(2).get_balance(), 13040.0);
}