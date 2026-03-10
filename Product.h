//
// Created by joaorodolfo on 09/03/2026.
//

#ifndef CALISTO_PRODUCT_H
#define CALISTO_PRODUCT_H
#include <string>
#include <utility>


class Product {
    int id;
    std::string name;

public:
    Product(const int id, std::string name)
        : id(id),
          name(std::move(name)) {
    }
};


#endif //CALISTO_PRODUCT_H
