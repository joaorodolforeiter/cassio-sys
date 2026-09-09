#include "domain/PriceQuote.h"

bool PriceQuote::isValid(double price) {
    return price > 0.0;
}


