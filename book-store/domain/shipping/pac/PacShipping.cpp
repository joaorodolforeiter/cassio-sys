#include "domain/shipping/pac/PacShipping.h"

#include <stdexcept>

#define FIRST_CLASS_SHIPPING_PRICE 10.0
#define SECOND_CLASS_SHIPPING_PRICE 15.0

double PacShipping::calculateCost(const Weight &totalWeight) const {
    if (totalWeight.isLessThanOrEqual(Weight(1000))) {
        return FIRST_CLASS_SHIPPING_PRICE;
    }

    if (totalWeight.isLessThanOrEqual(Weight(2000))) {
        return SECOND_CLASS_SHIPPING_PRICE;
    }

    throw std::invalid_argument("PAC nao aceita pedidos acima de 2kg.");
}



