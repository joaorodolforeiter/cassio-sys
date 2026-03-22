cmake_minimum_required(VERSION 3.10)
project(stock_exchange)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wshadow")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

# Source files
set(SOURCES
    main.cpp
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

# Header files
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

# Main executable
add_executable(stock_exchange ${SOURCES} ${HEADERS})
target_include_directories(stock_exchange PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Test executable
set(TEST_SOURCES
    tests.cpp
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

add_executable(tests ${TEST_SOURCES} ${HEADERS})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

