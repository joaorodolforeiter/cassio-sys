#ifndef CALISTO_ORDER_H
#define CALISTO_ORDER_H
#include "Weight.h"


class Order {
    const Weight weight;

public:
    explicit Order(const Weight &weight)
        : weight(weight) {
    }
};


#endif //CALISTO_ORDER_H