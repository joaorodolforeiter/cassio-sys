#include <iostream>

#include "Weight.h"

int main() {
    const Weight weight(1000);

    std::cout << weight.getKilos() << std::endl;
}
