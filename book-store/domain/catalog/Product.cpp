//
// Created by joaorodolfo on 09/03/2026.
//

#include "domain/catalog/Product.h"

#include <utility>

Product::Product(std::string name, const double price, const Weight &weight)
    : name(std::move(name)),
      price(price),
      weight(weight) {
}

const std::string &Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

Weight Product::getWeight() const {
    return weight;
}

