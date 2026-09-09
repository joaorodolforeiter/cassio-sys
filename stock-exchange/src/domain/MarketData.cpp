#include "domain/MarketData.h"
#include "domain/Stock.h"
#include <stdexcept>

MarketData::MarketData(std::shared_ptr<Stock> stock,
                       unsigned int volume,
                       double high,
                       double low)
    : m_stock(stock)
    , m_volume(volume)
    , m_high(high)
    , m_low(low)
{
    validate();
}

void MarketData::validate() const {
    if (!m_stock) {
        throw std::invalid_argument("MarketData: stock cannot be null");
    }
    if (m_high <= 0.0 || m_low <= 0.0) {
        throw std::invalid_argument("MarketData: high and low prices must be greater than 0");
    }
    if (m_high < m_low) {
        throw std::invalid_argument("MarketData: high price must be >= low price");
    }
}

std::shared_ptr<Stock> MarketData::getStock() const {
    return m_stock;
}

unsigned int MarketData::getVolume() const {
    return m_volume;
}

double MarketData::getHigh() const {
    return m_high;
}

double MarketData::getLow() const {
    return m_low;
}


