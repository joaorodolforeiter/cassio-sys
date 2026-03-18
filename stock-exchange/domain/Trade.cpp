#include "Trade.h"
#include "Order.h"
#include <stdexcept>

Trade::Trade(std::shared_ptr<Order> buyOrder,
             std::shared_ptr<Order> sellOrder,
             unsigned int executedQty,
             double price)
    : m_buyOrder(buyOrder)
    , m_sellOrder(sellOrder)
    , m_executedQty(executedQty)
    , m_price(price)
{
    if (!buyOrder || !sellOrder)
        throw std::invalid_argument("Trade: orders cannot be null");
    if (executedQty == 0)
        throw std::invalid_argument("Trade: executedQty must be > 0");
    if (price <= 0.0)
        throw std::invalid_argument("Trade: price must be > 0");
}

std::shared_ptr<Order> Trade::getBuyOrder() const {
    return m_buyOrder;
}

std::shared_ptr<Order> Trade::getSellOrder() const {
    return m_sellOrder;
}

unsigned int Trade::getExecutedQty() const {
    return m_executedQty;
}

double Trade::totalValue() const {
    return static_cast<double>(m_executedQty) * m_price;
}