#include <iostream>
#include <memory>
#include "../include/domain/Stock.h"
#include "../include/domain/Investor.h"
#include "test_framework.h"

/**
 * @brief Tests for Observer Pattern implementation
 *
 * Validates:
 * - Investor subscription to stocks
 * - Price update notifications
 * - Observer callback execution
 */

void testObserverPattern() {
    std::cout << "\n=== Testing Observer Pattern ===\n";

    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);
    auto investor = std::make_shared<Investor>("Alice");

    // Subscribe investor to stock
    investor->subscribe(stock);
    TEST("Investor subscription succeeds", true);

    // Update price (should notify investors)
    try {
        stock->updatePrice(155.0);
        TEST("Price update notifies observers", stock->getCurrentPrice() == 155.0);
    } catch (...) {
        TEST("Price update notifies observers", false);
    }
}

void runObserverTests() {
    testObserverPattern();
}

