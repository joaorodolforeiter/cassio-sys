cmake_minimum_required(VERSION 4.1)
project(stock_exchange)

set(CMAKE_CXX_STANDARD 26)

add_executable(stock_exchange main.cpp
        domain/Trade.cpp
        domain/Trade.h
        domain/Order.cpp
        domain/Order.h)
