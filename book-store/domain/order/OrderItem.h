//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef BOOK_STORE_ORDERITEM_H
#define BOOK_STORE_ORDERITEM_H

#include "domain/catalog/Product.h"


class OrderItem final {
    Product product;
    unsigned int quantity;

public:
    OrderItem(const Product &product, unsigned int quantity);

    [[nodiscard]] Product getProduct() const;
    [[nodiscard]] unsigned int getQuantity() const;
    [[nodiscard]] Weight totalWeight() const;
    [[nodiscard]] double totalPrice() const;
};


#endif // BOOK_STORE_ORDERITEM_H

