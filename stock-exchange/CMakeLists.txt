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
# Test sources from test/ directory
set(TEST_SOURCES
    test/main.cpp
    test/test_order.cpp
    test/test_stock.cpp
    test/test_matching.cpp
    test/test_portfolio.cpp
    test/test_exchange.cpp
    test/test_observer.cpp
    ${DOMAIN_SOURCES}
    ${HEADERS}
)

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/test)

# Add test as a CTest test
add_test(NAME StockExchangeTests COMMAND tests)

# ============== BUILD OPTIONS ==============
# Option to enable/disable debug symbols
option(ENABLE_DEBUG_SYMBOLS "Enable debug symbols" ON)
if(ENABLE_DEBUG_SYMBOLS)
    if(MSVC)
        target_compile_options(stock_exchange PRIVATE /Zi)
        target_compile_options(tests PRIVATE /Zi)
    else()
        target_compile_options(stock_exchange PRIVATE -g)
        target_compile_options(tests PRIVATE -g)
    endif()
endif()

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


