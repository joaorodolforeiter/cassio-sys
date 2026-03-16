#ifndef BOOK_STORE_SHIPPINGMETHOD_H
#define BOOK_STORE_SHIPPINGMETHOD_H

#include "../order/Weight.h"

class ShippingMethod {
public:
    virtual ~ShippingMethod() = default;
    [[nodiscard]] virtual double calculateCost(const Weight &totalWeight) const = 0;
};

#endif // BOOK_STORE_SHIPPINGMETHOD_H


