#include "domain/Stock.h"
#include "domain/Order.h"
#include "domain/Trade.h"
#include "domain/StockObserver.h"
#include <stdexcept>
#include <algorithm>

Stock::Stock(const std::string& symbol, const std::string& name, double initialPrice)
    : m_symbol(symbol)
    , m_name(name)
    , m_currentPrice(initialPrice)
{
    validate();
}

void Stock::validate() const {
    if (m_symbol.empty()) {
        throw std::invalid_argument("Stock: symbol cannot be empty");
    }
    if (m_name.empty()) {
        throw std::invalid_argument("Stock: name cannot be empty");
    }
    if (m_currentPrice <= 0.0) {
        throw std::invalid_argument("Stock: initial price must be greater than 0");
    }
}

void Stock::registerObserver(std::shared_ptr<StockObserver> observer) {
    if (!observer) {
        throw std::invalid_argument("Stock: observer cannot be null");
    }
    // Avoid duplicate observers
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it == m_observers.end()) {
        m_observers.push_back(observer);
    }
}

void Stock::removeObserver(std::shared_ptr<StockObserver> observer) {
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it != m_observers.end()) {
        m_observers.erase(it);
    }
}

void Stock::notifyObservers() {
    for (const auto& observer : m_observers) {
        observer->update(*this);
    }
}

const std::string& Stock::getSymbol() const {
    return m_symbol;
}

const std::string& Stock::getName() const {
    return m_name;
}

double Stock::getCurrentPrice() const {
    return m_currentPrice;
}

const std::vector<std::shared_ptr<Order>>& Stock::getOrders() const {
    return m_orders;
}

void Stock::addOrder(std::shared_ptr<Order> order) {
    if (!order) {
        throw std::invalid_argument("Stock: order cannot be null");
    }
    m_orders.push_back(order);
}

bool Stock::findMatchingOrders(size_t& buyOrderIndex, size_t& sellOrderIndex) const {
    std::shared_ptr<Order> buyOrder;
    std::shared_ptr<Order> sellOrder;
    size_t buyIdx = 0;
    size_t sellIdx = 0;

    // Find first BUY order with remaining quantity
    for (size_t i = 0; i < m_orders.size(); ++i) {
        if (m_orders[i]->getType() == OrderType::BUY &&
            m_orders[i]->getRemainingQuantity() > 0) {
            buyOrder = m_orders[i];
            buyIdx = i;
            break;
        }
    }

    // Find first SELL order with remaining quantity
    for (size_t i = 0; i < m_orders.size(); ++i) {
        if (m_orders[i]->getType() == OrderType::SELL &&
            m_orders[i]->getRemainingQuantity() > 0) {
            sellOrder = m_orders[i];
            sellIdx = i;
            break;
        }
    }

    // Check if we found both orders and prices match
    if (buyOrder && sellOrder && buyOrder->getValue() >= sellOrder->getValue()) {
        buyOrderIndex = buyIdx;
        sellOrderIndex = sellIdx;
        return true;
    }

    return false;
}

std::optional<Trade> Stock::matchOrders() {
    size_t buyIdx = 0;
    size_t sellIdx = 0;

    if (!findMatchingOrders(buyIdx, sellIdx)) {
        return std::nullopt;
    }

    auto buyOrder = m_orders[buyIdx];
    auto sellOrder = m_orders[sellIdx];

    // Determine execution quantity (minimum of both orders)
    unsigned int executedQty = std::min(
        buyOrder->getRemainingQuantity(),
        sellOrder->getRemainingQuantity()
    );

    // Use the sell order's price (seller sets the price)
    double executionPrice = sellOrder->getValue();

    // Update orders with executed quantities
    buyOrder->reduceQuantity(executedQty);
    sellOrder->reduceQuantity(executedQty);

    // Create and return the trade
    Trade trade(buyOrder, sellOrder, executedQty, executionPrice);

    // Remove fully executed orders (optional optimization)
    // This keeps the order book cleaner
    if (buyOrder->getRemainingQuantity() == 0 && sellOrder->getRemainingQuantity() == 0) {
        m_orders.erase(std::remove_if(m_orders.begin(), m_orders.end(),
            [](const std::shared_ptr<Order>& order) {
                return order->getRemainingQuantity() == 0;
            }), m_orders.end());
    }

    // Notify observers of the trade execution
    notifyObservers();

    return trade;
}

void Stock::updatePrice(double price) {
    if (price <= 0.0) {
        throw std::invalid_argument("Stock: price must be greater than 0");
    }
    m_currentPrice = price;
    notifyObservers();
}


