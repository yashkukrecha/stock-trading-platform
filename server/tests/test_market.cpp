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
    Stock s("TSLA", "Tesla Inc.", 400.56);
    market->add_stock(s, 1000);

    auto market_vector = market->get_market();
    int size = market_vector.size();
    EXPECT_EQ(size, 1);
    EXPECT_FLOAT_EQ(market_vector[0].first.get_price(), 400.56);

    const auto& m = market->get_market();
    auto& ob = const_cast<OrderBook&>(m.at(0).second); 
    auto best_bid_ask = ob.get_best_bid_ask();
    EXPECT_FLOAT_EQ(best_bid_ask.first, 0.0);
    EXPECT_FLOAT_EQ(best_bid_ask.second, 400.56);
}

// Test 3: Verify Trader Activities
TEST_F(MarketTest, AddAndGetTraderInfo) {
    market->add_trader(1, 1000.0);
    EXPECT_EQ(market->get_trader_info(1), "Balance: 1000.00\nYour stocks: N/A\n");
    EXPECT_FLOAT_EQ(market->get_trader(1).get_balance(), 1000.0);
    
    // Should not overwrite the existing trader
    market->add_trader(1, 2000.0);
    EXPECT_EQ(market->get_trader_info(1), "Balance: 1000.00\nYour stocks: N/A\n");
    EXPECT_FLOAT_EQ(market->get_trader(1).get_balance(), 1000.0);

    EXPECT_EQ(market->get_trader_info(2), "No trader found");
    EXPECT_THROW(market->get_trader(2), runtime_error);
}

// Test 4: Verify Adding Orders
TEST_F(MarketTest, AddOrder) {
    EXPECT_EQ(market->add_order(1, ""), "Trader does not exist");
    
    market->add_trader(1, 5000.0);
    market->add_trader(2, 5000.0);

    // Error checking
    EXPECT_EQ(market->add_order(1, "A"), "Invalid request");
    EXPECT_EQ(market->add_order(1, "BUY:TSLA:0"), "Must order at least 1 stock");
    EXPECT_EQ(market->add_order(1, "BUY:TSLA:100"), "Stock does not exist");

    Stock s("TSLA", "Tesla Inc.", 400.0);
    market->add_stock(s, 2);

    // Error checking
    EXPECT_EQ(market->add_order(1, "BUY:TSLA:100"), "Not enough funds for buy request");
    EXPECT_EQ(market->add_order(1, "SELL:TSLA:100"), "Not enough assets for sell request");
    EXPECT_EQ(market->add_order(1, "LOL:TSLA:100"), "Invalid request");

    // Trader 1 buys Tesla stock successfully
    EXPECT_EQ(market->add_order(1, "BUY:TSLA:2"), "Buy order added successfully: 2 shares @ 400.00");
    EXPECT_EQ(market->get_trader(1).get_quantity("TSLA"), 2);
    EXPECT_FLOAT_EQ(market->get_trader(1).get_balance(), 4200.0);

    // Trader 1 sells 1 Tesla stock, Trader 2 wants to buy 2 Tesla stock
    EXPECT_EQ(market->add_order(1, "SELL:TSLA:1"), "Sell order added successfully: 1 shares @ 400.00");
    EXPECT_EQ(market->add_order(2, "BUY:TSLA:2"), "Buy order added successfully: 2 shares @ 400.00");

    EXPECT_EQ(market->get_trader(1).get_quantity("TSLA"), 1);
    EXPECT_FLOAT_EQ(market->get_trader(1).get_balance(), 4600.0);
    EXPECT_EQ(market->get_trader(2).get_quantity("TSLA"), 1);
    EXPECT_FLOAT_EQ(market->get_trader(2).get_balance(), 4600.0);

    EXPECT_EQ(market->get_trader_info(1), "Balance: 4600.00\nYour stocks:\n"
                                          "1 shares of TSLA\n");
    EXPECT_EQ(market->get_trader_info(2), "Balance: 4600.00\nYour stocks:\n"
                                          "1 shares of TSLA\n");

}

// Test 5: Verify Recommending Stocks
TEST_F(MarketTest, RecommendStocks) {
    Stock s("TSLA", "Tesla Inc.", 400.0);
    Stock s2("AAPL", "Apple Inc.", 250.0);
    Stock s3("GOOG", "Google", 200.0);
    market->add_stock(s, 1000);
    market->add_stock(s2, 1000);
    market->add_stock(s3, 1000);

    for (int i = 0; i < 5; i++) {
        s2.brownian_motion();
    }

    for (int i = 0; i < 1000; i++) {
        s3.brownian_motion();
    }

    // Error checking
    EXPECT_EQ(market->recommend_stocks("RECOMMEND"), "Invalid request");
    EXPECT_EQ(market->recommend_stocks("RECOMMEN:10:10"), "Invalid request");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:HELLO:10"), "Invalid request");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:10:HELLO"), "Invalid request");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:10:0"), "Must request at least 1 stock");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:0:10"), "Risk tolerance must be a number between 1 and 3");

    // Recommendation of 1 stock at all three levels based on standard deviations
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:1:1"), "Recommended stocks: TSLA");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:2:1"), "Recommended stocks: AAPL");
    EXPECT_EQ(market->recommend_stocks("RECOMMEND:3:1"), "Recommended stocks: GOOG");
}