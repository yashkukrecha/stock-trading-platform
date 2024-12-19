#include "order.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

class OrderTest : public ::testing::Test {
protected:
    void SetUp() override {
        order = new Order(1, 100, 50.6, OrderType::BUY);
        order2 = new Order(2, 60, 58.2, OrderType::BUY);
        order3 = new Order(3, 45, 49.3, OrderType::SELL);
        order4 = new Order(4, 90, 62.3, OrderType::SELL);
    }

    void TearDown() override {
        delete order;
        delete order2;
        delete order3;
        delete order4;
    }

    Order *order;
    Order *order2;
    Order *order3;
    Order *order4;
};

// Test 1: Verify Constructor
TEST_F(OrderTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(order->get_trader_id(), 1);
    EXPECT_EQ(order->get_quantity(), 100);
    EXPECT_FLOAT_EQ(order->get_price(), 50.6);
    EXPECT_EQ(order->get_order_type(), OrderType::BUY);

    EXPECT_EQ(order3->get_trader_id(), 3);
    EXPECT_EQ(order3->get_quantity(), 45);
    EXPECT_FLOAT_EQ(order3->get_price(), 49.3);
    EXPECT_EQ(order3->get_order_type(), OrderType::SELL);
}

// Test 2: Verify Reducing Quantity
TEST_F(OrderTest, ReduceQuantity) {
    bool result = order->reduce_quantity(50);
    ASSERT_FALSE(result);

    result = order->reduce_quantity(50);
    ASSERT_TRUE(result);
    
    ASSERT_THROW(order->reduce_quantity(-10), out_of_range);
    ASSERT_THROW(order->reduce_quantity(10), out_of_range);
}

// Test 3: Verify > and < Operators
TEST_F(OrderTest, VerifyOperators) {
    bool result = (*order < *order2);
    ASSERT_TRUE(result);

    result = (*order > *order2);
    ASSERT_FALSE(result);

    result = (*order3 < *order4);
    ASSERT_FALSE(result);

    result = (*order3 > *order4);
    ASSERT_TRUE(result);
}