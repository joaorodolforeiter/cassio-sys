#ifndef STOCK_EXCHANGE_EXCHANGE_H
#define STOCK_EXCHANGE_EXCHANGE_H

#include <memory>
#include <vector>
#include <optional>
#include <string>

class Stock;
class Investor;
class Trade;
#include "MarketData.h"

/**
 * @brief Represents the stock exchange itself.
 *
 * Manages stocks and investors, and processes orders between them.
 * Follows the Single Responsibility Principle by focusing on exchange management.
 * Implements the Facade pattern to simplify client interaction with complex subsystems.
 */
class Exchange {
public:
    /**
     * @brief Create a new exchange
     */
    Exchange();

    virtual ~Exchange() = default;

    /**
     * @brief Register a stock on the exchange
     * @param stock The stock to register
     * @throws std::invalid_argument if stock is null or already registered
     */
    void registerStock(std::shared_ptr<Stock> stock);

    /**
     * @brief Register an investor on the exchange
     * @param investor The investor to register
     * @throws std::invalid_argument if investor is null or already registered
     */
    void registerInvestor(std::shared_ptr<Investor> investor);

    /**
     * @brief Process orders for a specific stock (match buy/sell orders)
     * @param stock The stock to process orders for
     * @return Optional trade if orders were matched, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<Trade> processOrders(std::shared_ptr<Stock> stock);

    /**
     * @brief Find a stock by symbol
     * @param symbol The stock symbol
     * @return Optional stock if found, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<std::shared_ptr<Stock>> getStock(
        const std::string& symbol) const;

    /**
     * @brief Get market data for a stock
     * @param stock The stock
     * @return Market data for the stock
     */
    [[nodiscard]] std::optional<MarketData> getMarketData(
        std::shared_ptr<Stock> stock) const;

    /**
     * @brief Get all registered stocks
     * @return Const reference to stocks vector
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Stock>>& getStocks() const;

    /**
     * @brief Get all registered investors
     * @return Const reference to investors vector
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Investor>>& getInvestors() const;

private:
    std::vector<std::shared_ptr<Stock>> m_stocks;
    std::vector<std::shared_ptr<Investor>> m_investors;
};

#endif //STOCK_EXCHANGE_EXCHANGE_H

