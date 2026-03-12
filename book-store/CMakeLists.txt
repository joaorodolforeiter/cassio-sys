cmake_minimum_required(VERSION 4.1)
project(book_store)

set(CMAKE_CXX_STANDARD 26)

add_executable(calisto main.cpp
        Order.cpp
        Order.h
        Weight.cpp
        Weight.h
        OrderItem.cpp
        OrderItem.h
        Product.cpp
        Product.h)
