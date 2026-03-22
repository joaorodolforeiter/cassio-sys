#include <iostream>
#include <memory>
#include "../include/domain/Exchange.h"
#include "../include/domain/Stock.h"
#include "../include/domain/Investor.h"
#include "../include/domain/MarketData.h"
#include "test_framework.h"

/**
 * @brief Tests for Exchange class (Facade)
 *
 * Validates:
 * - Stock registration
 * - Investor registration
 * - Stock lookup
 * - Market data retrieval
 * - Duplicate prevention
 */

void testExchange() {
    std::cout << "\n=== Testing Exchange ===\n";

    auto exchange = std::make_shared<Exchange>();
    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);
    auto investor = std::make_shared<Investor>("Alice");

    exchange->registerStock(stock);
    exchange->registerInvestor(investor);

    TEST("Register stock", exchange->getStocks().size() == 1);
    TEST("Register investor", exchange->getInvestors().size() == 1);

    auto foundStock = exchange->getStock("APPL");
    TEST("Find stock by symbol", foundStock.has_value());

    auto marketData = exchange->getMarketData(stock);
    TEST("Get market data", marketData.has_value());

    // Duplicate stock registration
    try {
        exchange->registerStock(stock);
        TEST("Reject duplicate stock", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject duplicate stock", true);
    }
}

void runExchangeTests() {
    testExchange();
}


