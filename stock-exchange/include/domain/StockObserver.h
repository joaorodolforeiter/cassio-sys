#ifndef STOCK_EXCHANGE_STOCK_OBSERVER_H
#define STOCK_EXCHANGE_STOCK_OBSERVER_H

class Stock;

/**
 * @brief Observer interface for stock price and order updates.
 *
 * Implements the Observer design pattern (Gang of Four).
 * Follows the Dependency Inversion Principle by depending on abstractions.
 * Follows the Interface Segregation Principle by defining a minimal interface.
 */
class StockObserver {
public:
    virtual ~StockObserver() = default;

    /**
     * @brief Called when a stock's state changes (price update, order execution, etc.)
     * @param stock The stock that changed
     */
    virtual void update(const Stock& stock) = 0;
};

#endif //STOCK_EXCHANGE_STOCK_OBSERVER_H

