#include "domain/shipping/pac/PacShipping.h"

#include <stdexcept>

double PacShipping::calculateCost(const Weight &totalWeight) const {
    if (totalWeight.isLessThanOrEqual(Weight(1000))) {
        return 10.0;
    }

    if (totalWeight.isLessThanOrEqual(Weight(2000))) {
        return 15.0;
    }

    throw std::invalid_argument("PAC nao aceita pedidos acima de 2kg.");
}



