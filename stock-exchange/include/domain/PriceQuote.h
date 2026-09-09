#ifndef STOCK_EXCHANGE_PRICE_QUOTE_H
#define STOCK_EXCHANGE_PRICE_QUOTE_H

/**
 * @brief Encapsulates price validation logic.
 *
 * Follows the Single Responsibility Principle by isolating
 * price validation into a dedicated utility.
 */
class PriceQuote {
public:
    /**
     * @brief Validate if a price is valid (positive)
     * @param price The price to validate
     * @return true if price > 0, false otherwise
     */
    static bool isValid(double price);
};

#endif //STOCK_EXCHANGE_PRICE_QUOTE_H

