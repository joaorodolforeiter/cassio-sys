cmake_minimum_required(VERSION 3.10)
project(stock_exchange CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wshadow")

# Debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing
enable_testing()

# Include FetchContent for Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

# ============== DOMAIN SOURCES ==============
set(DOMAIN_SOURCES
    src/domain/Order.cpp
    src/domain/Trade.cpp
    src/domain/Stock.cpp
    src/domain/Holding.cpp
    src/domain/Portfolio.cpp
    src/domain/Investor.cpp
    src/domain/MarketData.cpp
    src/domain/Exchange.cpp
    src/domain/PriceQuote.cpp
)

# ============== HEADERS ==============
set(HEADERS
    include/domain/OrderType.h
    include/domain/Order.h
    include/domain/Trade.h
    include/domain/Stock.h
    include/domain/StockObserver.h
    include/domain/StockSubject.h
    include/domain/Holding.h
    include/domain/Portfolio.h
    include/domain/Investor.h
    include/domain/MarketData.h
    include/domain/Exchange.h
    include/domain/PriceQuote.h
)

# ============== MAIN APPLICATION ==============
# Main executable (for debugging in CLion)
add_executable(stock_exchange
    main.cpp
    ${DOMAIN_SOURCES}
    ${HEADERS}
)

target_include_directories(stock_exchange PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ============== TEST EXECUTABLE ==============
# Test sources from test/ directory using Catch2
add_executable(stock_exchange_tests
    test/OrderTests.cpp
    test/OrderMatchingTests.cpp
    test/PortfolioTests.cpp
    test/ObserverTests.cpp
    test/StockTests.cpp
    test/ExchangeTests.cpp
        ${DOMAIN_SOURCES}
        ${HEADERS}
)

target_include_directories(stock_exchange_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(stock_exchange_tests PRIVATE Catch2::Catch2WithMain)

# Add test as a CTest test
add_test(NAME StockExchangeTests COMMAND stock_exchange_tests)


# Print build info
message(STATUS "========================================")
message(STATUS "Stock Exchange System - CMake Config")
message(STATUS "========================================")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Debug Symbols: ${ENABLE_DEBUG_SYMBOLS}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "========================================")
message(STATUS "Targets:")
message(STATUS "  - stock_exchange (main application)")
message(STATUS "  - tests (unit tests)")
message(STATUS "========================================")


