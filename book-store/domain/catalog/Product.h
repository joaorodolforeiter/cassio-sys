//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef BOOK_STORE_PRODUCT_H
#define BOOK_STORE_PRODUCT_H

#include <string>

#include "../order/Weight.h"

class Product final {
    std::string name;
    double price;
    Weight weight;

public:
    Product(std::string name, double price, const Weight &weight);

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] double getPrice() const;
    [[nodiscard]] Weight getWeight() const;
};

#endif // BOOK_STORE_PRODUCT_H

