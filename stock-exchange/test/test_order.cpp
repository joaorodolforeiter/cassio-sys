#include <iostream>
#include <memory>
#include "../include/domain/Order.h"
#include "../include/domain/Stock.h"
#include "test_framework.h"

/**
 * @brief Tests for Order class
 *
 * Validates:
 * - Order creation with valid parameters
 * - Validation of invalid parameters
 * - Order state management
 */

void testOrderValidation() {
    std::cout << "\n=== Testing Order Validation ===\n";

    auto stock = std::make_shared<Stock>("TEST", "Test Stock", 100.0);

    // Valid order
    try {
        auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, 99.50);
        TEST("Create valid order", true);
    } catch (...) {
        TEST("Create valid order", false);
    }

    // Null stock
    try {
        auto order = std::make_shared<Order>(nullptr, "Alice", 100, OrderType::BUY, 99.50);
        TEST("Reject null stock", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject null stock", true);
    }

    // Empty investor name
    try {
        auto order = std::make_shared<Order>(stock, "", 100, OrderType::BUY, 99.50);
        TEST("Reject empty investor name", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject empty investor name", true);
    }

    // Zero quantity
    try {
        auto order = std::make_shared<Order>(stock, "Alice", 0, OrderType::BUY, 99.50);
        TEST("Reject zero quantity", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject zero quantity", true);
    }

    // Negative price
    try {
        auto order = std::make_shared<Order>(stock, "Alice", 100, OrderType::BUY, -10.0);
        TEST("Reject negative price", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject negative price", true);
    }
}

void runOrderTests() {
    testOrderValidation();
}

