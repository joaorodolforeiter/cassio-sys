#ifndef STOCK_EXCHANGE_ORDER_H
#define STOCK_EXCHANGE_ORDER_H

#include "OrderType.h"
#include <memory>
#include <string>

class Stock;
class Trade;

/**
 * @brief Represents a buy or sell order for a stock.
 *
 * Follows the Single Responsibility Principle by handling only order data and validation.
 * Follows the Dependency Inversion Principle by depending on Stock through forward declaration.
 */
class Order {
public:
    /**
     * @brief Create a new order
     * @param stock The stock being ordered
     * @param investorName Name of the investor placing the order
     * @param quantity Number of shares
     * @param type Order type (BUY or SELL)
     * @param value Price per share
     * @throws std::invalid_argument if parameters are invalid
     */
    Order(std::shared_ptr<Stock> stock,
          const std::string& investorName,
          unsigned int quantity,
          OrderType type,
          double value);

    // Const-correct getters
    [[nodiscard]] std::shared_ptr<Stock> getStock() const;
    [[nodiscard]] const std::string& getInvestorName() const;
    [[nodiscard]] unsigned int getQuantity() const;
    [[nodiscard]] OrderType getType() const;
    [[nodiscard]] double getValue() const;

    // Quantity tracking
    [[nodiscard]] unsigned int getRemainingQuantity() const;
    void reduceQuantity(unsigned int executedQty);

private:
    std::shared_ptr<Stock> m_stock;
    std::string            m_investorName;
    unsigned int           m_quantity;
    unsigned int           m_remainingQuantity; ///< Tracks partial fills
    OrderType              m_type;
    double                 m_value;

    /**
     * @brief Validate order parameters
     * @throws std::invalid_argument if any parameter is invalid
     */
    void validate() const;
};

#endif //STOCK_EXCHANGE_ORDER_H

