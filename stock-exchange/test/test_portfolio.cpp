#include <iostream>
#include <memory>
#include <cmath>
#include "../include/domain/Portfolio.h"
#include "../include/domain/Holding.h"
#include "../include/domain/Stock.h"
#include "test_framework.h"

/**
 * @brief Tests for Portfolio and Holding classes
 *
 * Validates:
 * - Portfolio creation and management
 * - Holding management
 * - Position tracking
 * - Portfolio valuation
 */

void testPortfolio() {
    std::cout << "\n=== Testing Portfolio ===\n";

    auto portfolio = std::make_shared<Portfolio>();
    auto stock1 = std::make_shared<Stock>("APPL", "Apple", 150.0);
    auto stock2 = std::make_shared<Stock>("MSFT", "Microsoft", 300.0);

    auto holding1 = std::make_shared<Holding>(stock1, 100);
    portfolio->addHolding(holding1);

    TEST("Add holding to portfolio", portfolio->getHoldings().size() == 1);

    // Calculate total value: 100 shares * $150 = $15,000
    double expectedValue = 100 * 150.0;
    TEST("Portfolio total value calculation", std::abs(portfolio->totalValue() - expectedValue) < 0.01);

    // Add more shares of same stock
    auto holding2 = std::make_shared<Holding>(stock1, 50);
    portfolio->addHolding(holding2);

    TEST("Portfolio merges same stock holdings", portfolio->getHoldings().size() == 1);

    auto holding = portfolio->getHolding(stock1);
    TEST("Get holding for stock", holding.has_value());
    if (holding.has_value()) {
        TEST("Merged holding has correct quantity", holding.value()->getQuantity() == 150);
    }
}

void runPortfolioTests() {
    testPortfolio();
}

