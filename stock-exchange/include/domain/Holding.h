#ifndef STOCK_EXCHANGE_HOLDING_H
#define STOCK_EXCHANGE_HOLDING_H

#include <memory>

class Stock;

/**
 * @brief Represents a holding of shares of a single stock.
 *
 * Encapsulates the relationship between an investor and a stock position.
 * Follows the Single Responsibility Principle by managing only one stock position.
 */
class Holding {
public:
    /**
     * @brief Create a new holding
     * @param stock The stock being held
     * @param quantity The number of shares held
     * @throws std::invalid_argument if parameters are invalid
     */
    Holding(std::shared_ptr<Stock> stock, unsigned int quantity);

    // Const-correct getters
    [[nodiscard]] std::shared_ptr<Stock> getStock() const;
    [[nodiscard]] unsigned int getQuantity() const;

    // Quantity management
    void addQuantity(unsigned int qty);
    void removeQuantity(unsigned int qty);

private:
    std::shared_ptr<Stock> m_stock;
    unsigned int m_quantity;

    /**
     * @brief Validate holding parameters
     * @throws std::invalid_argument if any parameter is invalid
     */
    void validate() const;
};

#endif //STOCK_EXCHANGE_HOLDING_H

