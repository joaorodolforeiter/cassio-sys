#ifndef STOCK_EXCHANGE_STOCK_SUBJECT_H
#define STOCK_EXCHANGE_STOCK_SUBJECT_H

#include <memory>

class StockObserver;

/**
 * @brief Subject interface for the Observer design pattern.
 *
 * Defines the contract for observable stocks.
 * Follows the Dependency Inversion Principle by depending on abstractions.
 * Follows the Interface Segregation Principle by defining a minimal interface.
 */
class StockSubject {
public:
    virtual ~StockSubject() = default;

    /**
     * @brief Register an observer to receive notifications
     * @param observer The observer to register
     */
    virtual void registerObserver(std::shared_ptr<StockObserver> observer) = 0;

    /**
     * @brief Remove an observer from notifications
     * @param observer The observer to remove
     */
    virtual void removeObserver(std::shared_ptr<StockObserver> observer) = 0;

    /**
     * @brief Notify all observers of state changes
     */
    virtual void notifyObservers() = 0;
};

#endif //STOCK_EXCHANGE_STOCK_SUBJECT_H

