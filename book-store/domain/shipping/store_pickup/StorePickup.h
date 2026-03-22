#ifndef BOOK_STORE_STOREPICKUP_H
#define BOOK_STORE_STOREPICKUP_H

#include "domain/shipping/ShippingMethod.h"

class StorePickup final : public ShippingMethod {
public:
    [[nodiscard]] double calculateCost(const Weight &totalWeight) const override;
};

#endif // BOOK_STORE_STOREPICKUP_H



