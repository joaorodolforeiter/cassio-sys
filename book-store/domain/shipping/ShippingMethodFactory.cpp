#include "domain/shipping/ShippingMethodFactory.h"

#include <stdexcept>

#include "domain/shipping/pac/PacShipping.h"
#include "domain/shipping/sedex/SedexShipping.h"
#include "domain/shipping/store_pickup/StorePickup.h"

std::unique_ptr<ShippingMethod> ShippingMethodFactory::create(const ShippingMethodType type) {
    switch (type) {
        case ShippingMethodType::Pac:
            return std::make_unique<PacShipping>();
        case ShippingMethodType::Sedex:
            return std::make_unique<SedexShipping>();
        case ShippingMethodType::StorePickup:
            return std::make_unique<StorePickup>();
    }

    throw std::invalid_argument("Unsupported shipping method type.");
}

