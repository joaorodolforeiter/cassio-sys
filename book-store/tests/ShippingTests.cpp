#include <stdexcept>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "domain/catalog/Product.h"
#include "domain/order/Order.h"
#include "domain/order/OrderItem.h"
#include "domain/shipping/ShippingMethodFactory.h"
#include "../domain/order/Weight.h"

using Catch::Matchers::WithinAbs;

namespace {
Order createOrderWithTotalWeight(const unsigned int grams, const ShippingMethodType shippingType) {
    const Product synthetic("Synthetic", 10.0, Weight(grams));
    Order order(ShippingMethodFactory::create(shippingType));
    order.addItem(OrderItem(synthetic, 1));
    return order;
}
}

TEST_CASE("PAC costs R$10.00 up to 1kg", "[shipping][pac]") {
    const Order order = createOrderWithTotalWeight(1000, ShippingMethodType::Pac);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(10.0, 0.0001));
}

TEST_CASE("PAC costs R$15.00 from above 1kg to 2kg", "[shipping][pac]") {
    const Order order = createOrderWithTotalWeight(2000, ShippingMethodType::Pac);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(15.0, 0.0001));
}

TEST_CASE("PAC rejects orders above 2kg", "[shipping][pac]") {
    const Order order = createOrderWithTotalWeight(2001, ShippingMethodType::Pac);

    REQUIRE_THROWS_AS(order.deliveryCost(), std::invalid_argument);
}

TEST_CASE("Sedex costs R$12.50 up to 500g", "[shipping][sedex]") {
    const Order order = createOrderWithTotalWeight(500, ShippingMethodType::Sedex);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(12.5, 0.0001));
}

TEST_CASE("Sedex costs R$20.00 from above 500g to 1kg", "[shipping][sedex]") {
    const Order order = createOrderWithTotalWeight(1000, ShippingMethodType::Sedex);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(20.0, 0.0001));
}

TEST_CASE("Sedex charges base plus R$1.50 for each additional 100g", "[shipping][sedex]") {
    const Order order = createOrderWithTotalWeight(1250, ShippingMethodType::Sedex);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(51.0, 0.0001));
}

TEST_CASE("Store pickup has no delivery cost", "[shipping][pickup]") {
    const Order order = createOrderWithTotalWeight(5000, ShippingMethodType::StorePickup);

    REQUIRE_THAT(order.deliveryCost(), WithinAbs(0.0, 0.0001));
}

TEST_CASE("Order total weight aggregates item quantities", "[order]") {
    const Product first("Book A", 50.0, Weight(300));
    const Product second("Book B", 70.0, Weight(500));

    Order order(ShippingMethodFactory::create(ShippingMethodType::StorePickup));
    order.addItem(OrderItem(first, 2));
    order.addItem(OrderItem(second, 1));

    REQUIRE(order.totalWeight().inGrams() == 1100);
}

