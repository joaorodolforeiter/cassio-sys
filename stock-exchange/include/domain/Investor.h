#ifndef STOCK_EXCHANGE_INVESTOR_H
#define STOCK_EXCHANGE_INVESTOR_H

#include "StockObserver.h"
#include "OrderType.h"
#include <memory>
#include <string>
#include <vector>

class Portfolio;
class Stock;
class Order;

/**
 * @brief Represents an investor in the stock exchange.
 *
 * Implements the StockObserver interface to receive notifications about
 * stocks they are subscribed to.
 *
 * Follows the Single Responsibility Principle by focusing on investor operations.
 * Follows the Liskov Substitution Principle by implementing StockObserver correctly.
 */
class Investor : public StockObserver {
public:
    /**
     * @brief Create a new investor
     * @param name The investor's name
     * @throws std::invalid_argument if name is empty
     */
    explicit Investor(const std::string& name);

    virtual ~Investor() = default;

    // Getters (const-correct)
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] std::shared_ptr<Portfolio> getPortfolio() const;

    // Observer pattern
    void update(const Stock& stock) override;

    // Subscription management
    void subscribe(std::shared_ptr<Stock> stock);
    void unsubscribe(std::shared_ptr<Stock> stock);

    /**
     * @brief Place a buy or sell order
     * @param stock The stock to order
     * @param quantity Number of shares
     * @param type Order type (BUY or SELL)
     * @param price Price per share
     * @return The created order
     * @throws std::invalid_argument if parameters are invalid
     */
    std::shared_ptr<Order> placeOrder(
        std::shared_ptr<Stock> stock,
        unsigned int quantity,
        OrderType type,
        double price);

private:
    std::string m_name;
    std::shared_ptr<Portfolio> m_portfolio;
    std::vector<std::shared_ptr<Stock>> m_subscriptions;

    /**
     * @brief Validate investor name
     * @throws std::invalid_argument if name is empty
     */
    void validate() const;
};

#endif //STOCK_EXCHANGE_INVESTOR_H

