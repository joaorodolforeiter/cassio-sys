#include "domain/Holding.h"
#include "domain/Stock.h"
#include <stdexcept>
#include <sstream>

Holding::Holding(std::shared_ptr<Stock> stock, unsigned int quantity)
    : m_stock(stock)
    , m_quantity(quantity)
{
    validate();
}

void Holding::validate() const {
    if (!m_stock) {
        throw std::invalid_argument("Holding: stock cannot be null");
    }
    if (m_quantity == 0) {
        throw std::invalid_argument("Holding: quantity must be greater than 0");
    }
}

std::shared_ptr<Stock> Holding::getStock() const {
    return m_stock;
}

unsigned int Holding::getQuantity() const {
    return m_quantity;
}

void Holding::addQuantity(unsigned int qty) {
    if (qty == 0) {
        throw std::invalid_argument("Holding: quantity to add must be greater than 0");
    }
    m_quantity += qty;
}

void Holding::removeQuantity(unsigned int qty) {
    if (qty > m_quantity) {
        std::ostringstream oss;
        oss << "Holding: cannot remove " << qty
            << " shares, only " << m_quantity << " available";
        throw std::invalid_argument(oss.str());
    }
    m_quantity -= qty;
}


