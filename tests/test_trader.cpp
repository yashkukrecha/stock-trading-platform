#include "market.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

class TraderTest : public ::testing::Test {
protected:
    void SetUp() override {
        t = new Trader(1000.0);
        t2 = new Trader();
    }

    void TearDown() override {
        delete t;
        delete t2;
    }

    Trader *t;
    Trader *t2;
};

// Test 1: Verify Constructor
TEST_F(TraderTest, ConstructorInitializesCorrectly) {
    int balance = t->get_balance();
    EXPECT_FLOAT_EQ(balance, 1000.0);

    balance = t2->get_balance();
    EXPECT_FLOAT_EQ(balance, 0.0);
}

// Test 2: Verify Updating Balance
TEST_F(TraderTest, UpdateBalance) {
    t->update_balance(1000);
    EXPECT_FLOAT_EQ(t->get_balance(), 2000.0);

    t->update_balance(-1500.0);
    EXPECT_FLOAT_EQ(t->get_balance(), 500.0);
}

// Test 3: Verify Adding Stocks
TEST_F(TraderTest, AddStock) {
    t->add_stock("TSLA", 200);
    t->add_stock("AAPL", 100);
    EXPECT_EQ(t->get_quantity("TSLA"), 200);
    EXPECT_EQ(t->get_quantity("AAPL"), 100);
    EXPECT_EQ(t->get_stocks(), 
          "Balance: 1000.0\nYour stocks:\n"
          "100 shares of AAPL\n"
          "200 shares of TSLA\n");
}

// Test 4: Verify Updating Stock Quantities
TEST_F(TraderTest, UpdateQuantity) {
    t->add_stock("TSLA", 200);
    t->add_stock("AAPL", 100);
    EXPECT_EQ(t->get_quantity("TSLA"), 200);
    EXPECT_EQ(t->get_quantity("AAPL"), 100);

    t->update_quantity("TSLA", 300);
    EXPECT_EQ(t->get_quantity("TSLA"), 500);

    t->update_quantity("LOL", 100);
    EXPECT_EQ(t->get_quantity("TSLA"), 500);
    EXPECT_EQ(t->get_quantity("AAPL"), 100);
    EXPECT_EQ(t->get_stocks(), 
          "Balance: 1000.0\nYour stocks:\n"
          "100 shares of AAPL\n"
          "500 shares of TSLA\n");

    t->update_quantity("AAPL", -100);
    EXPECT_EQ(t->get_quantity("AAPL"), 0);
    EXPECT_EQ(t->get_stocks(), 
          "Balance: 1000.0\nYour stocks:\n"
          "500 shares of TSLA\n");
}