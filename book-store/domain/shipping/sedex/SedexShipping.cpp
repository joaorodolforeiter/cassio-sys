#include "domain/shipping/sedex/SedexShipping.h"

#include <cmath>

#define FIRST_CLASS_SHIPPING_PRICE 12.5
#define SECOND_CLASS_SHIPPING_PRICE 20.0

#define THIRD_CLASS_SHIPPING_BASE_PRICE 46.5
#define THIRD_CLASS_SHIPPING_BLOCK_RATE 1.5

#define BLOCK_SIZE 100


double SedexShipping::calculateCost(const Weight &totalWeight) const {
    if (totalWeight.isLessThanOrEqual(Weight(500))) {
        return FIRST_CLASS_SHIPPING_PRICE;
    }

    if (totalWeight.isLessThanOrEqual(Weight(1000))) {
        return SECOND_CLASS_SHIPPING_PRICE;
    }

    return calculateThirdClassShippingPrice(totalWeight);
}

double SedexShipping::calculateThirdClassShippingPrice(const Weight &totalWeight) {
    const unsigned int additionalGrams = totalWeight.inGrams() - 1000;
    const double additionalBlocks = std::ceil(static_cast<double>(additionalGrams) / BLOCK_SIZE);

    return THIRD_CLASS_SHIPPING_BASE_PRICE + (additionalBlocks * THIRD_CLASS_SHIPPING_BLOCK_RATE);
}
