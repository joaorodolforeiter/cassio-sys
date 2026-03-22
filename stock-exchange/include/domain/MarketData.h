#ifndef STOCK_EXCHANGE_MARKET_DATA_H
#define STOCK_EXCHANGE_MARKET_DATA_H

#include <memory>

class Stock;

/**
 * @brief Encapsulates market data for a stock.
 *
 * Tracks trading statistics such as volume, high and low prices.
 * Follows the Single Responsibility Principle by focusing only on data aggregation.
 */
class MarketData {
public:
    /**
     * @brief Create market data for a stock
     * @param stock The stock this data refers to
     * @param volume The trading volume
     * @param high The highest price in the session
     * @param low The lowest price in the session
     * @throws std::invalid_argument if parameters are invalid
     */
    MarketData(std::shared_ptr<Stock> stock,
               unsigned int volume,
               double high,
               double low);

    // Const-correct getters
    [[nodiscard]] std::shared_ptr<Stock> getStock() const;
    [[nodiscard]] unsigned int getVolume() const;
    [[nodiscard]] double getHigh() const;
    [[nodiscard]] double getLow() const;

private:
    std::shared_ptr<Stock> m_stock;
    unsigned int m_volume;
    double m_high;
    double m_low;

    /**
     * @brief Validate market data parameters
     * @throws std::invalid_argument if any parameter is invalid
     */
    void validate() const;
};

#endif //STOCK_EXCHANGE_MARKET_DATA_H

