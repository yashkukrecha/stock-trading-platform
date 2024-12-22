#include "market.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

class MarketTest : public ::testing::Test {
protected:
    void SetUp() override {
        market = new Market();
    }

    void TearDown() override {
        delete market;
    }

    Market *market;
};

// Test 1: Verify Constructor
TEST_F(MarketTest, ConstructorInitializesCorrectly) {
    int size = market->get_market().size();
    EXPECT_EQ(size, 0);
}

// Test 2: Verify Adding Stocks
TEST_F(MarketTest, AddStock) {
    Stock s("TLSA", "Tesla Inc.", 400.56);
    market->add_stock(s);

    auto market_vector = market->get_market();
    int size = market_vector.size();
    EXPECT_EQ(size, 1);
    EXPECT_FLOAT_EQ(market_vector[0].first.get_price(), 400.56);
}

// Test 3: Verify Trader Activities
TEST_F(MarketTest, AddAndGetTraderInfo) {
    market->add_trader(1, 1000.0);
    EXPECT_EQ(market->get_trader_info(1), "Balance: 1000.0\nYour stocks:\n");
    
    // Should not overwrite the existing trader
    market->add_trader(1, 2000.0);
    EXPECT_EQ(market->get_trader_info(1), "Balance: 1000.0\nYour stocks:\n");

    EXPECT_EQ(market->get_trader_info(2), "No trader found");
}