#include <iostream>

#include "domain/catalog/Product.h"
#include "domain/order/Order.h"
#include "domain/order/OrderItem.h"
#include "domain/shipping/ShippingMethodFactory.h"
#include "domain/order/Weight.h"

int main() {
    const Product cleanCode("Clean Code", 89.9, Weight(450));
    const Product designPatterns("Design Patterns", 149.9, Weight(700));

    Order order(ShippingMethodFactory::create(ShippingMethodType::Pac));
    order.addItem(OrderItem(cleanCode, 1));
    order.addItem(OrderItem(designPatterns, 1));

    std::cout << "Peso total (g): " << order.totalWeight().inGrams() << '\n';
    std::cout << "Frete PAC: R$ " << order.deliveryCost() << '\n';

    order.changeShippingMethod(ShippingMethodFactory::create(ShippingMethodType::Sedex));
    std::cout << "Frete Sedex: R$ " << order.deliveryCost() << '\n';

    order.changeShippingMethod(ShippingMethodFactory::create(ShippingMethodType::StorePickup));
    std::cout << "Retirada na loja: R$ " << order.deliveryCost() << '\n';

    return 0;
}
