cmake_minimum_required(VERSION 4.1)
project(stock_exchange)

set(CMAKE_CXX_STANDARD 26)

add_executable(stock_exchange main.cpp
        src/domain/Trade.cpp
        include/domain/Trade.h
        src/domain/Order.cpp
        include/domain/Order.h)
