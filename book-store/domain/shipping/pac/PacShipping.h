#ifndef BOOK_STORE_PACSHIPPING_H
#define BOOK_STORE_PACSHIPPING_H

#include "domain/shipping/ShippingMethod.h"

class PacShipping final : public ShippingMethod {
public:
    [[nodiscard]] double calculateCost(const Weight &totalWeight) const override;
};

#endif // BOOK_STORE_PACSHIPPING_H



