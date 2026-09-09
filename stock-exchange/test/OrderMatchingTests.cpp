#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "domain/Stock.h"
#include "domain/Order.h"
#include "domain/Trade.h"

/**
 * @brief Tests for Order Matching functionality
 *
 * Validates:
 * - Basic order matching
 * - Partial order fills
 * - Order quantity tracking
 * - Trade creation
 */

namespace {
    std::shared_ptr<Stock> createStock(const std::string& symbol = "APPL",
                                       const std::string& name = "Apple",
                                       double price = 150.0) {
        return std::make_shared<Stock>(symbol, name, price);
    }
}

TEST_CASE("Match orders when prices align", "[matching]") {
    auto stock = createStock();

    // Place buy order at higher price
    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    // Place sell order at lower price (should match)
    auto sellOrder = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 150.0);
    stock->addOrder(sellOrder);

    auto trade = stock->matchOrders();
    REQUIRE(trade.has_value());
}

TEST_CASE("Trade executes at correct quantity", "[matching]") {
    auto stock = createStock();

    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    auto sellOrder = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 150.0);
    stock->addOrder(sellOrder);

    auto trade = stock->matchOrders();
    REQUIRE(trade.has_value());
    REQUIRE(trade.value().getExecutedQty() == 50);
}

TEST_CASE("Trade updates remaining quantities", "[matching]") {
    auto stock = createStock();

    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    auto sellOrder = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 150.0);
    stock->addOrder(sellOrder);

    auto trade = stock->matchOrders();
    REQUIRE(trade.has_value());

    REQUIRE(buyOrder->getRemainingQuantity() == 50);
    REQUIRE(sellOrder->getRemainingQuantity() == 0);
}

TEST_CASE("Partial fills - multiple sell orders against single buy", "[matching][partial]") {
    auto stock = createStock("MSFT", "Microsoft", 300.0);

    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 301.0);
    stock->addOrder(buyOrder);

    auto sellOrder1 = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 300.0);
    stock->addOrder(sellOrder1);

    // First trade: 50 shares
    auto trade1 = stock->matchOrders();
    REQUIRE(trade1.has_value());
    REQUIRE(trade1.value().getExecutedQty() == 50);

    // Add second sell order
    auto sellOrder2 = std::make_shared<Order>(stock, "Charlie", 50, OrderType::SELL, 300.0);
    stock->addOrder(sellOrder2);

    // Second trade: remaining 50 shares
    auto trade2 = stock->matchOrders();
    REQUIRE(trade2.has_value());
    REQUIRE(trade2.value().getExecutedQty() == 50);
    REQUIRE(buyOrder->getRemainingQuantity() == 0);
}

TEST_CASE("Buy order with insufficient matching sell orders", "[matching]") {
    auto stock = createStock();

    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    auto sellOrder = std::make_shared<Order>(stock, "Bob", 50, OrderType::SELL, 160.0);
    stock->addOrder(sellOrder);

    // Prices don't match, no trade should occur
    auto trade = stock->matchOrders();
    REQUIRE(!trade.has_value());
}

TEST_CASE("Trade value calculation", "[matching]") {
    auto stock = createStock();

    auto buyOrder = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 151.0);
    stock->addOrder(buyOrder);

    auto sellOrder = std::make_shared<Order>(stock, "Bob", 100, OrderType::SELL, 150.0);
    stock->addOrder(sellOrder);

    auto trade = stock->matchOrders();
    REQUIRE(trade.has_value());
    REQUIRE(trade.value().totalValue() == 100 * 150.0);
}

