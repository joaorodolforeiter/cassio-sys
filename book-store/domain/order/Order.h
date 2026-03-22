#ifndef BOOK_STORE_ORDER_H
#define BOOK_STORE_ORDER_H

#include <memory>
#include <vector>

#include "domain/order/OrderItem.h"
#include "domain/shipping/ShippingMethod.h"

class Order final {
    std::vector<OrderItem> items;
    std::unique_ptr<ShippingMethod> shippingMethod;

public:
    explicit Order(std::unique_ptr<ShippingMethod> shippingMethod);

    Order(const Order &) = delete;
    Order &operator=(const Order &) = delete;
    Order(Order &&) noexcept = default;
    Order &operator=(Order &&) noexcept = default;

    void addItem(const OrderItem &item);

    [[nodiscard]] Weight totalWeight() const;
    [[nodiscard]] double totalPrice() const;
    [[nodiscard]] double deliveryCost() const;
};

#endif // BOOK_STORE_ORDER_H


