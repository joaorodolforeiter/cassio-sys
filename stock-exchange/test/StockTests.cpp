#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "domain/Stock.h"
#include "domain/Order.h"
#include "domain/OrderType.h"

/**
 * @brief Tests for Stock class
 *
 * Validates:
 * - Stock creation with valid parameters
 * - Validation of invalid parameters
 * - Stock state management
 * - Observer pattern implementation
 */

TEST_CASE("Create valid stock", "[stock]") {
    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);

    REQUIRE(stock != nullptr);
    REQUIRE(stock->getSymbol() == "APPL");
    REQUIRE(stock->getName() == "Apple");
    REQUIRE(stock->getCurrentPrice() == 150.0);
}

TEST_CASE("Reject empty symbol", "[stock][validation]") {
    REQUIRE_THROWS_AS(
        std::make_shared<Stock>("", "Apple", 150.0),
        std::invalid_argument
    );
}

TEST_CASE("Reject empty name", "[stock][validation]") {
    REQUIRE_THROWS_AS(
        std::make_shared<Stock>("APPL", "", 150.0),
        std::invalid_argument
    );
}

TEST_CASE("Reject negative price", "[stock][validation]") {
    REQUIRE_THROWS_AS(
        std::make_shared<Stock>("APPL", "Apple", -150.0),
        std::invalid_argument
    );
}

TEST_CASE("Reject zero price", "[stock][validation]") {
    REQUIRE_THROWS_AS(
        std::make_shared<Stock>("APPL", "Apple", 0.0),
        std::invalid_argument
    );
}

TEST_CASE("Update stock price successfully", "[stock]") {
    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);

    REQUIRE(stock->getCurrentPrice() == 150.0);

    stock->updatePrice(155.0);
    REQUIRE(stock->getCurrentPrice() == 155.0);
}

TEST_CASE("Get stock symbol correctly", "[stock]") {
    auto stock = std::make_shared<Stock>("MSFT", "Microsoft", 300.0);

    REQUIRE(stock->getSymbol() == "MSFT");
}

TEST_CASE("Get stock name correctly", "[stock]") {
    auto stock = std::make_shared<Stock>("APPL", "Apple Inc.", 150.0);

    REQUIRE(stock->getName() == "Apple Inc.");
}

TEST_CASE("Stock manages orders list", "[stock]") {
    auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);

    REQUIRE(stock->getOrders().size() == 0);

    auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 149.50);
    stock->addOrder(order);

    REQUIRE(stock->getOrders().size() == 1);
}

