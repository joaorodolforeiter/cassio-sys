//
// Created by joaorodolfo on 09/03/2026.
//

#include "domain/order/Weight.h"

Weight::Weight(const unsigned int grams) : grams(grams) {
}

unsigned int Weight::inGrams() const {
    return grams;
}

double Weight::inKilograms() const {
    return static_cast<double>(grams) / 1000.0;
}

Weight Weight::plus(const Weight &other) const {
    return Weight(grams + other.grams);
}

Weight Weight::times(const unsigned int multiplier) const {
    return Weight(grams * multiplier);
}

bool Weight::isLessThanOrEqual(const Weight &other) const {
    return grams <= other.grams;
}

bool Weight::isGreaterThan(const Weight &other) const {
    return grams > other.grams;
}

