#include "domain/Investor.h"
#include "domain/Portfolio.h"
#include "domain/Stock.h"
#include "domain/Order.h"
#include "domain/OrderType.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

Investor::Investor(const std::string& name)
    : m_name(name)
    , m_portfolio(std::make_shared<Portfolio>())
{
    validate();
}

void Investor::validate() const {
    if (m_name.empty()) {
        throw std::invalid_argument("Investor: name cannot be empty");
    }
}

const std::string& Investor::getName() const {
    return m_name;
}

std::shared_ptr<Portfolio> Investor::getPortfolio() const {
    return m_portfolio;
}

void Investor::subscribe(std::shared_ptr<Stock> stock) {
    if (!stock) {
        throw std::invalid_argument("Investor: stock cannot be null");
    }

    // Check if already subscribed
    auto it = std::find(m_subscriptions.begin(), m_subscriptions.end(), stock);
    if (it == m_subscriptions.end()) {
        m_subscriptions.push_back(stock);
        stock->registerObserver(std::make_shared<Investor>(*this));
    }
}

void Investor::unsubscribe(std::shared_ptr<Stock> stock) {
    if (!stock) {
        throw std::invalid_argument("Investor: stock cannot be null");
    }

    auto it = std::find(m_subscriptions.begin(), m_subscriptions.end(), stock);
    if (it != m_subscriptions.end()) {
        m_subscriptions.erase(it);
        // Note: In production, we'd need a way to unregister from the observer list
        // This would require storing the shared_ptr to self in the Stock
    }
}

std::shared_ptr<Order> Investor::placeOrder(
    std::shared_ptr<Stock> stock,
    unsigned int quantity,
    OrderType type,
    double price) {

    if (!stock) {
        throw std::invalid_argument("Investor: stock cannot be null");
    }

    auto order = std::make_shared<Order>(stock, m_name, quantity, type, price);
    stock->addOrder(order);
    return order;
}

void Investor::update(const Stock& stock) {
    // Notify investor of stock changes
    // In a real system, this could trigger re-evaluation of portfolio or alerts
    std::cout << "Investor " << m_name << " received update on stock "
              << stock.getSymbol() << " (current price: "
              << stock.getCurrentPrice() << ")" << std::endl;
}


