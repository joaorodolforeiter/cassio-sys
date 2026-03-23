cmake_minimum_required(VERSION 3.20)
project(book_store)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(book_store_domain
        domain/order/Order.cpp
        domain/order/Order.h
        domain/order/OrderItem.cpp
        domain/order/OrderItem.h
        domain/catalog/Product.cpp
        domain/catalog/Product.h
        domain/order/Weight.cpp
        domain/order/Weight.h
        domain/shipping/ShippingMethod.h
        domain/shipping/ShippingMethodFactory.cpp
        domain/shipping/ShippingMethodFactory.h
        domain/shipping/pac/PacShipping.cpp
        domain/shipping/pac/PacShipping.h
        domain/shipping/sedex/SedexShipping.cpp
        domain/shipping/sedex/SedexShipping.h
        domain/shipping/store_pickup/StorePickup.cpp
        domain/shipping/store_pickup/StorePickup.h)

target_include_directories(book_store_domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(book_store_tests tests/ShippingTests.cpp)
target_link_libraries(book_store_tests PRIVATE book_store_domain Catch2::Catch2WithMain)

add_test(NAME book_store_tests COMMAND book_store_tests)
