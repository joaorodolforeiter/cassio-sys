//
// Created by lkreuch on 18/03/2026.
//

#ifndef STOCK_EXCHANGE_TRADE_H
#define STOCK_EXCHANGE_TRADE_H
#include <memory>

class Order;

class Trade {

public:
    Trade(std::shared_ptr<Order> buyOrder,
        std::shared_ptr<Order> sellOrder,
        unsigned int executedQty,
        double price);

    std::shared_ptr<Order> getBuyOrder() const;
    std::shared_ptr<Order> getSellOrder() const;
    unsigned int getExecutedQty() const;
    double totalValue() const;

private:
    std::shared_ptr<Order>  m_buyOrder;
    std::shared_ptr<Order>  m_sellOrder;
    unsigned int            m_executedQty;
    double                  m_price;
};


#endif //STOCK_EXCHANGE_TRADE_H