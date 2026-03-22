#include <iostream>
#include "test_framework.h"

/**
 * @brief Test suite main file
 *
 * Declares and runs all test suites
 * Centralizes test execution and reporting
 */

// Forward declarations of test runner functions
void runOrderTests();
void runStockTests();
void runOrderMatchingTests();
void runPortfolioTests();
void runExchangeTests();
void runObserverTests();

int main() {
    std::cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Stock Exchange System - Unit Test Suite                 ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════╝\n";

    try {
        // Run all test suites
        runOrderTests();
        runStockTests();
        runOrderMatchingTests();
        runPortfolioTests();
        runExchangeTests();
        runObserverTests();

        // Print final summary
        auto& framework = TestFramework::getInstance();

        std::cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        std::cout << "║  Final Test Results                                       ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════╝\n";
        std::cout << "\nTotal Tests: " << framework.getTotalTests() << "\n";
        std::cout << "Passed:      " << framework.getPassedTests() << "\n";
        std::cout << "Failed:      " << (framework.getTotalTests() - framework.getPassedTests()) << "\n";

        if (framework.allPassed()) {
            std::cout << "\n✓ All tests passed!\n\n";
            return 0;
        } else {
            std::cout << "\n✗ Some tests failed!\n\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}

