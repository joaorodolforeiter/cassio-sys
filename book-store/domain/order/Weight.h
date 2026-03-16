//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef BOOK_STORE_WEIGHT_H
#define BOOK_STORE_WEIGHT_H


class Weight final {
    unsigned int grams;

public:
    explicit Weight(unsigned int grams);

    [[nodiscard]] unsigned int inGrams() const;
    [[nodiscard]] double inKilograms() const;

    [[nodiscard]] Weight plus(const Weight &other) const;
    [[nodiscard]] Weight times(unsigned int multiplier) const;

    [[nodiscard]] bool isLessThanOrEqual(const Weight &other) const;
    [[nodiscard]] bool isGreaterThan(const Weight &other) const;
};


#endif // BOOK_STORE_WEIGHT_H

