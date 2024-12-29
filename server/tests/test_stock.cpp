#include "stock.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

class StockTest : public ::testing::Test {
protected:
    void SetUp() override {
        stock = new Stock("AAPL", "Apple Inc.", 150.0);
        stock2 = new Stock("TSLA", "Tesla Inc.", 0.0);
    }

    void TearDown() override {
        delete stock;
        delete stock2;
    }

    Stock *stock;
    Stock *stock2;
};

// Test 1: Verify Constructor
TEST_F(StockTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(stock->get_symbol(), "AAPL");
    EXPECT_EQ(stock->get_name(), "Apple Inc.");
    EXPECT_FLOAT_EQ(stock->get_price(), 150.0);
    ASSERT_EQ(stock->get_price_history().size(), 1);
    EXPECT_FLOAT_EQ(stock->get_price_history()[0], 150.0);
}

// Test 2: Verify Brownian Motion
TEST_F(StockTest, BrownianMotion) {
    float old_price = stock->get_price();
    stock->brownian_motion();
    float new_price = stock->get_price();

    ASSERT_LE(abs(new_price - old_price), 0.5);
    ASSERT_EQ(stock->get_price_history().size(), 2);
    EXPECT_FLOAT_EQ(stock->get_price_history().back(), new_price);
}

// Test 3: Verify Standard Deviation
TEST_F(StockTest, StandardDeviation) {
    float old_price = stock->get_price();
    stock->brownian_motion();
    float new_price = stock->get_price();

    float mean = (old_price + new_price) / 2;
    float variance = 0;
    variance += ((old_price - mean) * (old_price - mean));
    variance += ((new_price - mean) * (new_price - mean));
    variance /= 2;
    variance = sqrt(variance);

    EXPECT_FLOAT_EQ(stock->standard_deviation(), variance);
    EXPECT_FLOAT_EQ(stock2->standard_deviation(), 0);
}

// Test 4: Prevent Negative Price Updates
TEST_F(StockTest, UpdatePriceRejectsNegativeValues) {
    for (int i = 0; i < 20; i++) {
        stock2->brownian_motion();
        ASSERT_GE(stock2->get_price(), 0);
    }
    ASSERT_EQ(stock2->get_price_history().size(), 21);
}