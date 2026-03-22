#include "domain/Portfolio.h"
#include "domain/Holding.h"
#include "domain/Stock.h"
#include <stdexcept>
#include <algorithm>

Portfolio::Portfolio() = default;

void Portfolio::addHolding(std::shared_ptr<Holding> holding) {
    if (!holding) {
        throw std::invalid_argument("Portfolio: holding cannot be null");
    }

    auto stock = holding->getStock();

    // Check if we already have this stock
    auto it = std::find_if(m_holdings.begin(), m_holdings.end(),
        [&stock](const std::shared_ptr<Holding>& h) {
            return h->getStock()->getSymbol() == stock->getSymbol();
        });

    if (it != m_holdings.end()) {
        // Update existing holding
        (*it)->addQuantity(holding->getQuantity());
    } else {
        // Add new holding
        m_holdings.push_back(holding);
    }
}

std::optional<std::shared_ptr<Holding>> Portfolio::getHolding(
    const std::shared_ptr<Stock>& stock) const {

    if (!stock) {
        throw std::invalid_argument("Portfolio: stock cannot be null");
    }

    auto it = std::find_if(m_holdings.begin(), m_holdings.end(),
        [&stock](const std::shared_ptr<Holding>& h) {
            return h->getStock()->getSymbol() == stock->getSymbol();
        });

    if (it != m_holdings.end()) {
        return *it;
    }

    return std::nullopt;
}

double Portfolio::totalValue() const {
    double total = 0.0;
    for (const auto& holding : m_holdings) {
        double holdingValue = static_cast<double>(holding->getQuantity())
                            * holding->getStock()->getCurrentPrice();
        total += holdingValue;
    }
    return total;
}

const std::vector<std::shared_ptr<Holding>>& Portfolio::getHoldings() const {
    return m_holdings;
}


