#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <memory>
#include <cmath>

#include "domain/Portfolio.h"
#include "domain/Holding.h"
#include "domain/Stock.h"

using Catch::Matchers::WithinAbs;

/**
 * @brief Tests for Portfolio and Holding classes
 *
 * Validates:
 * - Portfolio creation and management
 * - Holding management
 * - Position tracking
 * - Portfolio valuation
 */

namespace {
    std::shared_ptr<Stock> createStock(const std::string& symbol,
                                       const std::string& name,
                                       double price) {
        return std::make_shared<Stock>(symbol, name, price);
    }
}

TEST_CASE("Create empty portfolio", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();

    REQUIRE(portfolio != nullptr);
    REQUIRE(portfolio->getHoldings().size() == 0);
}

TEST_CASE("Add single holding to portfolio", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock = createStock("APPL", "Apple", 150.0);

    auto holding = std::make_shared<Holding>(stock, 100);
    portfolio->addHolding(holding);

    REQUIRE(portfolio->getHoldings().size() == 1);
}

TEST_CASE("Portfolio calculates total value correctly", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock = createStock("APPL", "Apple", 150.0);

    auto holding = std::make_shared<Holding>(stock, 100);
    portfolio->addHolding(holding);

    // Expected value: 100 shares * $150 = $15,000
    double expectedValue = 100 * 150.0;
    REQUIRE_THAT(portfolio->totalValue(), WithinAbs(expectedValue, 0.01));
}

TEST_CASE("Portfolio merges same stock holdings", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock = createStock("APPL", "Apple", 150.0);

    auto holding1 = std::make_shared<Holding>(stock, 100);
    portfolio->addHolding(holding1);

    auto holding2 = std::make_shared<Holding>(stock, 50);
    portfolio->addHolding(holding2);

    REQUIRE(portfolio->getHoldings().size() == 1);
}

TEST_CASE("Portfolio merged holdings have correct quantity", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock = createStock("APPL", "Apple", 150.0);

    auto holding1 = std::make_shared<Holding>(stock, 100);
    portfolio->addHolding(holding1);

    auto holding2 = std::make_shared<Holding>(stock, 50);
    portfolio->addHolding(holding2);

    auto holding = portfolio->getHolding(stock);
    REQUIRE(holding.has_value());
    REQUIRE(holding.value()->getQuantity() == 150);
}

TEST_CASE("Portfolio with multiple different stocks", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock1 = createStock("APPL", "Apple", 150.0);
    auto stock2 = createStock("MSFT", "Microsoft", 300.0);

    auto holding1 = std::make_shared<Holding>(stock1, 100);
    auto holding2 = std::make_shared<Holding>(stock2, 50);

    portfolio->addHolding(holding1);
    portfolio->addHolding(holding2);

    REQUIRE(portfolio->getHoldings().size() == 2);
}

TEST_CASE("Portfolio calculates total value with multiple stocks", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock1 = createStock("APPL", "Apple", 150.0);
    auto stock2 = createStock("MSFT", "Microsoft", 300.0);

    auto holding1 = std::make_shared<Holding>(stock1, 100);
    auto holding2 = std::make_shared<Holding>(stock2, 50);

    portfolio->addHolding(holding1);
    portfolio->addHolding(holding2);

    // Expected: (100 * 150) + (50 * 300) = 15000 + 15000 = 30000
    double expectedValue = (100 * 150.0) + (50 * 300.0);
    REQUIRE_THAT(portfolio->totalValue(), WithinAbs(expectedValue, 0.01));
}

TEST_CASE("Get holding for specific stock", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock = createStock("APPL", "Apple", 150.0);

    auto holding = std::make_shared<Holding>(stock, 100);
    portfolio->addHolding(holding);

    auto retrievedHolding = portfolio->getHolding(stock);
    REQUIRE(retrievedHolding.has_value());
    REQUIRE(retrievedHolding.value()->getStock() == stock);
}

TEST_CASE("Get holding for non-existent stock returns empty", "[portfolio]") {
    auto portfolio = std::make_shared<Portfolio>();
    auto stock1 = createStock("APPL", "Apple", 150.0);
    auto stock2 = createStock("MSFT", "Microsoft", 300.0);

    auto holding = std::make_shared<Holding>(stock1, 100);
    portfolio->addHolding(holding);

    auto retrievedHolding = portfolio->getHolding(stock2);
    REQUIRE(!retrievedHolding.has_value());
}

