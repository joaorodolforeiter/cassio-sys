//
// Created by joaorodolfo on 09/03/2026.
//

#include "domain/order/Order.h"

#include <stdexcept>

Order::Order(std::unique_ptr<ShippingMethod> shippingMethod)
    : shippingMethod(std::move(shippingMethod)) {
    if (!this->shippingMethod) {
        throw std::invalid_argument("Order requires a shipping method.");
    }
}

void Order::addItem(const OrderItem &item) {
    items.push_back(item);
}

void Order::changeShippingMethod(std::unique_ptr<ShippingMethod> shippingMethod) {
    if (!shippingMethod) {
        throw std::invalid_argument("Order requires a shipping method.");
    }

    this->shippingMethod = std::move(shippingMethod);
}

Weight Order::totalWeight() const {
    Weight accumulated(0);

    for (const auto &item: items) {
        accumulated = accumulated.plus(item.totalWeight());
    }

    return accumulated;
}

double Order::totalPrice() const {
    double total = 0.0;

    for (const auto &item: items) {
        total += item.totalPrice();
    }

    return total;
}

double Order::deliveryCost() const {
    return shippingMethod->calculateCost(totalWeight());
}

