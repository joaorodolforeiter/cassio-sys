#ifndef BOOK_STORE_SEDEXSHIPPING_H
#define BOOK_STORE_SEDEXSHIPPING_H

#include "domain/shipping/ShippingMethod.h"

class SedexShipping final : public ShippingMethod {
public:
    [[nodiscard]] double calculateCost(const Weight &totalWeight) const override;
private:
    [[nodiscard]] static double calculateThirdClassShippingPrice(const Weight &totalWeight);
};

#endif // BOOK_STORE_SEDEXSHIPPING_H



