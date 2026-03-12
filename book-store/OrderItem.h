//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef CALISTO_ORDERITEM_H
#define CALISTO_ORDERITEM_H
#include "Product.h"
#include "Weight.h"


class OrderItem {
    double price;
    Weight weight;
    Product product;

public:
    OrderItem(const Weight &weight, const Product &product)
        : weight(weight),
          product(product) {
    }

    [[nodiscard]] Weight getWeight() const {
        return weight;
    }

    [[nodiscard]] Product getProduct() const {
        return product;
    }
};


#endif //CALISTO_ORDERITEM_H
