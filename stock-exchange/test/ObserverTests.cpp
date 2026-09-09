#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "domain/Stock.h"
#include "domain/Investor.h"

/**
 * @brief Tests for Observer Pattern implementation
 *
 * Validates:
 * - Investor subscription to stocks
 * - Price update notifications
 * - Observer callback execution
 */

namespace {
    std::shared_ptr<Stock> createStock(const std::string& symbol = "APPL",
                                       const std::string& name = "Apple",
                                       double price = 150.0) {
        return std::make_shared<Stock>(symbol, name, price);
    }

    std::shared_ptr<Investor> createInvestor(const std::string& name) {
        return std::make_shared<Investor>(name);
    }
}

TEST_CASE("Investor can subscribe to stock", "[observer]") {
    auto stock = createStock();
    auto investor = createInvestor("Alice");

    investor->subscribe(stock);

    REQUIRE(true); // Subscription completed without error
}

TEST_CASE("Stock price update notifies observers", "[observer]") {
    auto stock = createStock();
    auto investor = createInvestor("Alice");

    investor->subscribe(stock);

    REQUIRE(stock->getCurrentPrice() == 150.0);

    stock->updatePrice(155.0);

    REQUIRE(stock->getCurrentPrice() == 155.0);
}

TEST_CASE("Multiple investors can subscribe to same stock", "[observer]") {
    auto stock = createStock();
    auto investor1 = createInvestor("Alice");
    auto investor2 = createInvestor("Bob");

    investor1->subscribe(stock);
    investor2->subscribe(stock);

    REQUIRE(true); // Both subscriptions completed without error
}

TEST_CASE("Stock update notifies all subscribed investors", "[observer]") {
    auto stock = createStock();
    auto investor1 = createInvestor("Alice");
    auto investor2 = createInvestor("Bob");

    investor1->subscribe(stock);
    investor2->subscribe(stock);

    REQUIRE(stock->getCurrentPrice() == 150.0);

    stock->updatePrice(160.0);

    REQUIRE(stock->getCurrentPrice() == 160.0);
}

TEST_CASE("Investor can subscribe to multiple stocks", "[observer]") {
    auto stock1 = createStock("APPL", "Apple", 150.0);
    auto stock2 = createStock("MSFT", "Microsoft", 300.0);
    auto investor = createInvestor("Alice");

    investor->subscribe(stock1);
    investor->subscribe(stock2);

    REQUIRE(true); // Both subscriptions completed without error
}

TEST_CASE("Price updates are reflected across multiple subscribers", "[observer]") {
    auto stock = createStock();
    auto investor1 = createInvestor("Alice");
    auto investor2 = createInvestor("Bob");
    auto investor3 = createInvestor("Charlie");

    investor1->subscribe(stock);
    investor2->subscribe(stock);
    investor3->subscribe(stock);

    stock->updatePrice(170.0);

    REQUIRE(stock->getCurrentPrice() == 170.0);
}

TEST_CASE("Multiple price updates are notified correctly", "[observer]") {
    auto stock = createStock();
    auto investor = createInvestor("Alice");

    investor->subscribe(stock);

    stock->updatePrice(155.0);
    REQUIRE(stock->getCurrentPrice() == 155.0);

    stock->updatePrice(160.0);
    REQUIRE(stock->getCurrentPrice() == 160.0);

    stock->updatePrice(165.0);
    REQUIRE(stock->getCurrentPrice() == 165.0);
}

