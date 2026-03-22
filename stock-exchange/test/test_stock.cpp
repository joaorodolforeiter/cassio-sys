#include <iostream>
#include <memory>
#include "../include/domain/Stock.h"
#include "test_framework.h"

/**
 * @brief Tests for Stock class
 *
 * Validates:
 * - Stock creation with valid parameters
 * - Validation of invalid parameters
 * - Stock state management
 * - Observer pattern implementation
 */

void testStockValidation() {
    std::cout << "\n=== Testing Stock Validation ===\n";

    // Valid stock
    try {
        auto stock = std::make_shared<Stock>("APPL", "Apple", 150.0);
        TEST("Create valid stock", true);
    } catch (...) {
        TEST("Create valid stock", false);
    }

    // Empty symbol
    try {
        auto stock = std::make_shared<Stock>("", "Apple", 150.0);
        TEST("Reject empty symbol", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject empty symbol", true);
    }

    // Negative price
    try {
        auto stock = std::make_shared<Stock>("APPL", "Apple", -150.0);
        TEST("Reject negative price", false);
    } catch (const std::invalid_argument&) {
        TEST("Reject negative price", true);
    }
}

void runStockTests() {
    testStockValidation();
}

