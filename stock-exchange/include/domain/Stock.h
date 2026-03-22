#ifndef STOCK_EXCHANGE_STOCK_H
#define STOCK_EXCHANGE_STOCK_H

#include "StockSubject.h"
#include "PriceQuote.h"
#include <memory>
#include <string>
#include <vector>
#include <optional>

class Order;
class Trade;
class StockObserver;

/**
 * @brief Represents a tradable stock on the exchange.
 *
 * Implements the StockSubject interface for the Observer pattern.
 * Manages orders and price updates.
 *
 * Follows the Single Responsibility Principle by focusing on stock management.
 * Follows the Open/Closed Principle by allowing extension via observers.
 * Follows the Liskov Substitution Principle by implementing StockSubject correctly.
 */
class Stock : public StockSubject {
public:
    /**
     * @brief Create a new stock
     * @param symbol The stock symbol (e.g., "APPL")
     * @param name The company name
     * @param initialPrice The initial trading price
     * @throws std::invalid_argument if parameters are invalid
     */
    Stock(const std::string& symbol, const std::string& name, double initialPrice);

    virtual ~Stock() = default;

    // StockSubject interface implementation
    void registerObserver(std::shared_ptr<StockObserver> observer) override;
    void removeObserver(std::shared_ptr<StockObserver> observer) override;
    void notifyObservers() override;

    // Getters (const-correct)
    [[nodiscard]] const std::string& getSymbol() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] double getCurrentPrice() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Order>>& getOrders() const;

    // Order management
    void addOrder(std::shared_ptr<Order> order);

    /**
     * @brief Match buy and sell orders
     * @return Optional Trade if orders could be matched, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<Trade> matchOrders();

    /**
     * @brief Update the stock price
     * @param price The new price
     * @throws std::invalid_argument if price is invalid
     */
    void updatePrice(double price);

private:
    std::string m_symbol;
    std::string m_name;
    double m_currentPrice;
    std::vector<std::shared_ptr<Order>> m_orders;
    std::vector<std::shared_ptr<StockObserver>> m_observers;

    /**
     * @brief Validate stock parameters
     * @throws std::invalid_argument if any parameter is invalid
     */
    void validate() const;

    /**
     * @brief Find the first BUY and SELL orders that can be matched
     * @param buyOrderIndex Output: index of matching BUY order
     * @param sellOrderIndex Output: index of matching SELL order
     * @return true if orders can be matched, false otherwise
     */
    bool findMatchingOrders(size_t& buyOrderIndex, size_t& sellOrderIndex) const;
};

#endif //STOCK_EXCHANGE_STOCK_H

