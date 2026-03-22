#ifndef BOOK_STORE_SHIPPINGMETHODFACTORY_H
#define BOOK_STORE_SHIPPINGMETHODFACTORY_H

#include <memory>

#include "domain/shipping/ShippingMethod.h"

enum class ShippingMethodType {
    Pac,
    Sedex,
    StorePickup
};

class ShippingMethodFactory final {
public:
    [[nodiscard]] static std::unique_ptr<ShippingMethod> create(ShippingMethodType type);
};

#endif // BOOK_STORE_SHIPPINGMETHODFACTORY_H

