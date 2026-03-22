#ifndef STOCK_EXCHANGE_ORDER_TYPE_H
#define STOCK_EXCHANGE_ORDER_TYPE_H

/**
 * @brief Enum representing the type of order
 *
 * Follows the Single Responsibility Principle by defining a single,
 * well-defined enum for order types.
 */
enum class OrderType {
    BUY,   ///< Buy order - investor wants to purchase stocks
    SELL   ///< Sell order - investor wants to sell stocks
};

#endif //STOCK_EXCHANGE_ORDER_TYPE_H

