#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "domain/Exchange.h"
#include "domain/Stock.h"
#include "domain/Investor.h"

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

namespace {
    std::shared_ptr<Stock> createStock(const std::string& symbol,
                                       const std::string& name,
                                       double price) {
        return std::make_shared<Stock>(symbol, name, price);
    }

    std::shared_ptr<Investor> createInvestor(const std::string& name) {
        return std::make_shared<Investor>(name);
    }
}

TEST_CASE("Create exchange", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();

    REQUIRE(exchange != nullptr);
    REQUIRE(exchange->getStocks().size() == 0);
    REQUIRE(exchange->getInvestors().size() == 0);
}

TEST_CASE("Register stock to exchange", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock = createStock("APPL", "Apple", 150.0);

    exchange->registerStock(stock);

    REQUIRE(exchange->getStocks().size() == 1);
}

TEST_CASE("Register investor to exchange", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto investor = createInvestor("Alice");

    exchange->registerInvestor(investor);

    REQUIRE(exchange->getInvestors().size() == 1);
}

TEST_CASE("Register multiple stocks", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock1 = createStock("APPL", "Apple", 150.0);
    auto stock2 = createStock("MSFT", "Microsoft", 300.0);

    exchange->registerStock(stock1);
    exchange->registerStock(stock2);

    REQUIRE(exchange->getStocks().size() == 2);
}

TEST_CASE("Register multiple investors", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto investor1 = createInvestor("Alice");
    auto investor2 = createInvestor("Bob");

    exchange->registerInvestor(investor1);
    exchange->registerInvestor(investor2);

    REQUIRE(exchange->getInvestors().size() == 2);
}

TEST_CASE("Find stock by symbol", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock = createStock("APPL", "Apple", 150.0);

    exchange->registerStock(stock);

    auto foundStock = exchange->getStock("APPL");
    REQUIRE(foundStock.has_value());
    REQUIRE(foundStock.value()->getSymbol() == "APPL");
}

TEST_CASE("Find non-existent stock returns empty", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock = createStock("APPL", "Apple", 150.0);

    exchange->registerStock(stock);

    auto foundStock = exchange->getStock("MSFT");
    REQUIRE(!foundStock.has_value());
}

TEST_CASE("Get market data for stock", "[exchange]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock = createStock("APPL", "Apple", 150.0);

    exchange->registerStock(stock);

    auto marketData = exchange->getMarketData(stock);
    REQUIRE(marketData.has_value());
}

TEST_CASE("Reject duplicate stock registration", "[exchange][validation]") {
    auto exchange = std::make_shared<Exchange>();
    auto stock = createStock("APPL", "Apple", 150.0);

    exchange->registerStock(stock);

    REQUIRE_THROWS_AS(
        exchange->registerStock(stock),
        std::invalid_argument
    );
}

TEST_CASE("Reject null stock registration", "[exchange][validation]") {
    auto exchange = std::make_shared<Exchange>();

    REQUIRE_THROWS_AS(
        exchange->registerStock(nullptr),
        std::invalid_argument
    );
}

TEST_CASE("Reject null investor registration", "[exchange][validation]") {
    auto exchange = std::make_shared<Exchange>();

    REQUIRE_THROWS_AS(
        exchange->registerInvestor(nullptr),
        std::invalid_argument
    );
}

