//
// Created by joaorodolfo on 09/03/2026.
//

#include "Weight.h"

unsigned int Weight::getGrams() const {
    return this->grams;
}

unsigned int Weight::getKilos() const {
    return this->grams / 1000;
}
