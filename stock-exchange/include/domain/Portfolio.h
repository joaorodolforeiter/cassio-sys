#ifndef STOCK_EXCHANGE_PORTFOLIO_H
#define STOCK_EXCHANGE_PORTFOLIO_H

#include <memory>
#include <vector>
#include <optional>

class Stock;
class Holding;

/**
 * @brief Manages an investor's stock holdings.
 *
 * Encapsulates the collection of stock positions owned by an investor.
 * Follows the Single Responsibility Principle by focusing only on portfolio management.
 * Provides a clean interface for buying/selling operations.
 */
class Portfolio {
public:
    /**
     * @brief Create an empty portfolio
     */
    Portfolio();

    /**
     * @brief Add or update a holding
     * @param holding The holding to add
     * @throws std::invalid_argument if holding is invalid
     */
    void addHolding(std::shared_ptr<Holding> holding);

    /**
     * @brief Get a holding for a specific stock
     * @param stock The stock to find
     * @return Optional holding if found, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<std::shared_ptr<Holding>> getHolding(
        const std::shared_ptr<Stock>& stock) const;

    /**
     * @brief Calculate the total value of the portfolio at current prices
     * @return The total value in currency units
     */
    [[nodiscard]] double totalValue() const;

    /**
     * @brief Get all holdings
     * @return Const reference to the holdings vector
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Holding>>& getHoldings() const;

private:
    std::vector<std::shared_ptr<Holding>> m_holdings;
};

#endif //STOCK_EXCHANGE_PORTFOLIO_H

