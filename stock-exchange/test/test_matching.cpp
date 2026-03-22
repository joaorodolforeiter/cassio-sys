#include <iostream>
#include <memory>
#include "../include/domain/Stock.h"
#include "../include/domain/Order.h"
#include "../include/domain/Trade.h"
#include "test_framework.h"

/**
 * @brief Tests for Order Matching functionality
 *
 * Validates:
 * - Basic order matching
 * - Partial order fills
 * - Order quantity tracking
 * - Trade creation
 */

void testOrderMatching() {
    std::cout << "\n=== Testing Order Matching ===\n";

    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);

    // Place buy order at higher price
    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    // Place sell order at lower price (should match)
    auto sellOrder = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 150.0);
    stock->addOrder(sellOrder);

    auto trade = stock->matchOrders();
    TEST("Match orders when prices align", trade.has_value());

    if (trade.has_value()) {
        TEST("Executed quantity is minimum of both orders", trade.value().getExecutedQty() == 50);
        TEST("Execution price is sell order price", trade.value().totalValue() == 50 * 150.0);
        TEST("Remaining buy quantity updated", buyOrder->getRemainingQuantity() == 50);
        TEST("Remaining sell quantity updated", sellOrder->getRemainingQuantity() == 0);
    }
}

void testPartialFills() {
    std::cout << "\n=== Testing Partial Order Fills ===\n";

    auto stock = std::make_shared<Stock>("MSFT", "Microsoft", 300.0);

    auto buyOrder1 = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 301.0);
    stock->addOrder(buyOrder1);

    auto sellOrder1 = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 300.0);
    stock->addOrder(sellOrder1);

    // First trade: 50 shares
    auto trade1 = stock->matchOrders();
    TEST("First partial fill succeeds", trade1.has_value());
    TEST("First trade is 50 shares", trade1.value().getExecutedQty() == 50);

    // Add second sell order
    auto sellOrder2 = std::make_shared<Order>(stock, "Charlie", 50, OrderType::SELL, 300.0);
    stock->addOrder(sellOrder2);

    // Second trade: remaining 50 shares
    auto trade2 = stock->matchOrders();
    TEST("Second partial fill succeeds", trade2.has_value());
    TEST("Second trade is 50 shares", trade2.value().getExecutedQty() == 50);
    TEST("Buy order fully executed", buyOrder1->getRemainingQuantity() == 0);
}

void runOrderMatchingTests() {
    testOrderMatching();
    testPartialFills();
}

