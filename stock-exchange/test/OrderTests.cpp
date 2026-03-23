#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "domain/Order.h"
#include "domain/Stock.h"

/**
 * @brief Tests for Order class
 *
 * Validates:
 * - Order creation with valid parameters
 * - Validation of invalid parameters
 * - Order state management
 */

namespace {
    std::shared_ptr<Stock> createStock(const std::string& symbol = "TEST",
                                       const std::string& name = "Test Stock",
                                       double price = 100.0) {
        return std::make_shared<Stock>(symbol, name, price);
    }
}

TEST_CASE("Create valid buy order", "[order]") {
    auto stock = createStock();
    auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);

    REQUIRE(order != nullptr);
    REQUIRE(order->getRemainingQuantity() == 100);
}

TEST_CASE("Create valid sell order", "[order]") {
    auto stock = createStock();
    auto order = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 101.00);

    REQUIRE(order != nullptr);
    REQUIRE(order->getRemainingQuantity() == 50);
}

TEST_CASE("Reject null stock", "[order][validation]") {
    REQUIRE_THROWS_AS(
        std::make_shared<Order>(nullptr, "Alice", 100, OrderType::BUY, 99.50),
        std::invalid_argument
    );
}

TEST_CASE("Reject empty investor name", "[order][validation]") {
    auto stock = createStock();
    REQUIRE_THROWS_AS(
        std::make_shared<Order>(stock, "", 100, OrderType::BUY, 99.50),
        std::invalid_argument
    );
}

TEST_CASE("Reject zero quantity", "[order][validation]") {
    auto stock = createStock();
    REQUIRE_THROWS_AS(
        std::make_shared<Order>(stock, "Alice", 0, OrderType::BUY, 99.50),
        std::invalid_argument
    );
}

TEST_CASE("Reject negative price", "[order][validation]") {
    auto stock = createStock();
    REQUIRE_THROWS_AS(
        std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, -10.0),
        std::invalid_argument
    );
}

TEST_CASE("Order tracks remaining quantity correctly", "[order]") {
    auto stock = createStock();
    auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);

    REQUIRE(order->getRemainingQuantity() == 100);

    // Simulate partial execution
    order->updateRemainingQuantity(50);
    REQUIRE(order->getRemainingQuantity() == 50);
}

TEST_CASE("Get order type correctly", "[order]") {
    auto stock = createStock();
    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);
    auto sellOrder = std::make_shared<Order>(stock, "Bob", 100, OrderType::SELL, 101.00);

    REQUIRE(buyOrder->getOrderType() == OrderType::BUY);
    REQUIRE(sellOrder->getOrderType() == OrderType::SELL);
}

TEST_CASE("Get order price correctly", "[order]") {
    auto stock = createStock();
    auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);

    REQUIRE(order->getPrice() == 99.50);
}

TEST_CASE("Get investor name correctly", "[order]") {
    auto stock = createStock();
    auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);

    REQUIRE(order->getInvestorName() == "Alice");
}

