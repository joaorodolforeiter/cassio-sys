#include "domain/Order.h"
#include "domain/Stock.h"
#include <stdexcept>
#include <sstream>

Order::Order(std::shared_ptr<Stock> stock,
             const std::string& investorName,
             unsigned int quantity,
             OrderType type,
             double value)
    : m_stock(stock)
    , m_investorName(investorName)
    , m_quantity(quantity)
    , m_remainingQuantity(quantity)
    , m_type(type)
    , m_value(value)
{
    validate();
}

void Order::validate() const {
    if (!m_stock) {
        throw std::invalid_argument("Order: stock cannot be null");
    }
    if (m_investorName.empty()) {
        throw std::invalid_argument("Order: investor name cannot be empty");
    }
    if (m_quantity == 0) {
        throw std::invalid_argument("Order: quantity must be greater than 0");
    }
    if (m_value <= 0.0) {
        throw std::invalid_argument("Order: value must be greater than 0");
    }
}

std::shared_ptr<Stock> Order::getStock() const {
    return m_stock;
}

const std::string& Order::getInvestorName() const {
    return m_investorName;
}

unsigned int Order::getQuantity() const {
    return m_quantity;
}

OrderType Order::getType() const {
    return m_type;
}

double Order::getValue() const {
    return m_value;
}

unsigned int Order::getRemainingQuantity() const {
    return m_remainingQuantity;
}

void Order::reduceQuantity(unsigned int executedQty) {
    if (executedQty > m_remainingQuantity) {
        std::ostringstream oss;
        oss << "Order: cannot execute " << executedQty
            << " shares, only " << m_remainingQuantity << " remaining";
        throw std::invalid_argument(oss.str());
    }
    m_remainingQuantity -= executedQty;
}

