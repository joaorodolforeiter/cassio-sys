//
// Created by joaorodolfo on 09/03/2026.
//

#include "domain/order/OrderItem.h"

OrderItem::OrderItem(const Product &product, const unsigned int quantity)
    : product(product),
      quantity(quantity) {
}

Product OrderItem::getProduct() const {
    return product;
}

unsigned int OrderItem::getQuantity() const {
    return quantity;
}

Weight OrderItem::totalWeight() const {
    return product.getWeight().times(quantity);
}

double OrderItem::totalPrice() const {
    return product.getPrice() * quantity;
}

