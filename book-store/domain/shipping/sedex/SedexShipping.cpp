#include "domain/shipping/sedex/SedexShipping.h"

#include <cmath>

double SedexShipping::calculateCost(const Weight &totalWeight) const {
    if (totalWeight.isLessThanOrEqual(Weight(500))) {
        return 12.5;
    }

    if (totalWeight.isLessThanOrEqual(Weight(1000))) {
        return 20.0;
    }

    const unsigned int additionalGrams = totalWeight.inGrams() - 1000;
    const double additionalBlocks = std::ceil(static_cast<double>(additionalGrams) / 100.0);

    return 46.5 + (additionalBlocks * 1.5);
}



