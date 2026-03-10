//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef CALISTO_WEIGHT_H
#define CALISTO_WEIGHT_H


class Weight final {
    const unsigned int grams;

public:
    explicit Weight(const unsigned int grams) : grams(grams) {
    }

    [[nodiscard]] unsigned int getGrams() const;

    [[nodiscard]] unsigned int getKilos() const;
};


#endif //CALISTO_WEIGHT_H
