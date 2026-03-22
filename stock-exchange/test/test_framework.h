#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

/**
 * @brief Simple test framework for Stock Exchange System
 *
 * Provides utilities for running and reporting test results
 */
class TestFramework {
public:
    struct TestResult {
        std::string testName;
        bool passed;
    };

    static TestFramework& getInstance() {
        static TestFramework instance;
        return instance;
    }

    void test(const std::string& name, bool condition) {
        totalTests++;
        if (condition) {
            std::cout << "✓ PASS: " << name << std::endl;
            passedTests++;
            results.push_back({name, true});
        } else {
            std::cout << "✗ FAIL: " << name << std::endl;
            results.push_back({name, false});
        }
    }

    void printSummary(const std::string& category = "") {
        std::cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        std::cout << "║  Test Results";
        if (!category.empty()) {
            std::cout << " - " << category;
        }
        std::cout << std::string(20, ' ') << "║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════╝\n";
        std::cout << "\nTotal Tests: " << totalTests << "\n";
        std::cout << "Passed:      " << passedTests << "\n";
        std::cout << "Failed:      " << (totalTests - passedTests) << "\n";
    }

    int getPassedTests() const { return passedTests; }
    int getTotalTests() const { return totalTests; }
    bool allPassed() const { return passedTests == totalTests; }

    void reset() {
        totalTests = 0;
        passedTests = 0;
        results.clear();
    }

private:
    TestFramework() : totalTests(0), passedTests(0) {}

    int totalTests;
    int passedTests;
    std::vector<TestResult> results;
};

// Convenience macro
#define TEST(name, condition) TestFramework::getInstance().test(name, condition)

#endif // TEST_FRAMEWORK_H

