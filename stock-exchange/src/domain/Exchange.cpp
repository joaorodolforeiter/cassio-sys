#include "domain/Exchange.h"
#include "domain/Stock.h"
#include "domain/Investor.h"
#include "domain/Trade.h"
#include "domain/MarketData.h"
#include "domain/Order.h"
#include <stdexcept>
#include <algorithm>

Exchange::Exchange() = default;

void Exchange::registerStock(std::shared_ptr<Stock> stock) {
    if (!stock) {
        throw std::invalid_argument("Exchange: stock cannot be null");
    }

    // Check if stock is already registered
    auto it = std::find_if(m_stocks.begin(), m_stocks.end(),
        [&stock](const std::shared_ptr<Stock>& s) {
            return s->getSymbol() == stock->getSymbol();
        });

    if (it != m_stocks.end()) {
        throw std::invalid_argument("Exchange: stock with symbol " + stock->getSymbol() +
                                   " is already registered");
    }

    m_stocks.push_back(stock);
}

void Exchange::registerInvestor(std::shared_ptr<Investor> investor) {
    if (!investor) {
        throw std::invalid_argument("Exchange: investor cannot be null");
    }

    // Check if investor is already registered
    auto it = std::find_if(m_investors.begin(), m_investors.end(),
        [&investor](const std::shared_ptr<Investor>& i) {
            return i->getName() == investor->getName();
        });

    if (it != m_investors.end()) {
        throw std::invalid_argument("Exchange: investor " + investor->getName() +
                                   " is already registered");
    }

    m_investors.push_back(investor);
}

std::optional<Trade> Exchange::processOrders(std::shared_ptr<Stock> stock) {
    if (!stock) {
        throw std::invalid_argument("Exchange: stock cannot be null");
    }

    return stock->matchOrders();
}

std::optional<std::shared_ptr<Stock>> Exchange::getStock(const std::string& symbol) const {
    if (symbol.empty()) {
        throw std::invalid_argument("Exchange: symbol cannot be empty");
    }

    auto it = std::find_if(m_stocks.begin(), m_stocks.end(),
        [&symbol](const std::shared_ptr<Stock>& s) {
            return s->getSymbol() == symbol;
        });

    if (it != m_stocks.end()) {
        return *it;
    }

    return std::nullopt;
}

std::optional<MarketData> Exchange::getMarketData(std::shared_ptr<Stock> stock) const {
    if (!stock) {
        throw std::invalid_argument("Exchange: stock cannot be null");
    }

    // Calculate market data from orders
    unsigned int volume = 0;
    double high = stock->getCurrentPrice();
    double low = stock->getCurrentPrice();

    const auto& orders = stock->getOrders();
    for (const auto& order : orders) {
        if (order->getValue() > high) {
            high = order->getValue();
        }
        if (order->getValue() < low) {
            low = order->getValue();
        }
        volume += order->getQuantity();
    }

    return MarketData(stock, volume, high, low);
}

const std::vector<std::shared_ptr<Stock>>& Exchange::getStocks() const {
    return m_stocks;
}

const std::vector<std::shared_ptr<Investor>>& Exchange::getInvestors() const {
    return m_investors;
}


