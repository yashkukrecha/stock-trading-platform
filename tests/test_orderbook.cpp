#include "orderbook.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

class OrderBookTest : public ::testing::Test {
protected:
    void SetUp() override {
        ob = new OrderBook("TSLA");
    }

    void TearDown() override {
        delete ob;
    }

    OrderBook *ob;
};

// Test 1: Verify Constructor
TEST_F(OrderBookTest, ConstructorInitializesCorrectly) {
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 0.0);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 0.0);
}

// Test 2: Verify Adding Order
TEST_F(OrderBookTest, AddOrder) {
    Order o(1, 100, 25.6, OrderType::BUY);
    ob->add_order(o);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 25.6);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 0.0);

    Order o2(1, 120, 32.4, OrderType::SELL);
    ob->add_order(o2);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 25.6);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 32.4);
}

// Test 3: Verify Matching Orders
TEST_F(OrderBookTest, MatchOrders) {

    // Matching happens inside of add_order --> called implicitly
    Order o(1, 100, 25.6, OrderType::BUY);
    ob->add_order(o);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 25.6);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 0.0);

    Order o2(1, 120, 32.4, OrderType::SELL);
    ob->add_order(o2);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 25.6);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 32.4);

    Order o3(1, 120, 20, OrderType::SELL);
    ob->add_order(o3);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 0.0);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 20.0);

    Order o4(1, 150, 76.4, OrderType::BUY);
    ob->add_order(o4);

    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().first, 76.4);
    EXPECT_FLOAT_EQ(ob->get_best_bid_ask().second, 0.0);
}