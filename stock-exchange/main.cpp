#include <iostream>
#include <iomanip>
#include <memory>
#include "domain/Exchange.h"
#include "domain/Stock.h"
#include "domain/Investor.h"
#include "domain/Order.h"
#include "domain/Trade.h"
#include "domain/Portfolio.h"
#include "domain/Holding.h"
#include "domain/MarketData.h"
#include "domain/OutputFormatter.h"

/**
 * @brief Classe responsável pela demonstração do sistema de bolsa de valores
 *
 * Encapsula toda a lógica de demonstração seguindo o princípio da responsabilidade única.
 */
class StockExchangeDemonstration {
private:
    std::shared_ptr<Exchange> exchange;
    std::shared_ptr<Stock> appleStock;
    std::shared_ptr<Stock> microsoftStock;
    std::shared_ptr<Stock> googleStock;
    std::shared_ptr<Investor> investor1;
    std::shared_ptr<Investor> investor2;
    std::shared_ptr<Investor> investor3;

public:
    /**
     * @brief Executa toda a demonstração do sistema
     */
    void run() {
        OutputFormatter::printSeparator(" Stock Exchange System - Demonstration ");

        createExchange();
        registerStocks();
        registerInvestors();
        subscribeToStocks();
        placeOrders();
        processOrders();
        updatePrices();
        displayPortfolios();
        displayMarketData();
        demonstrateErrorHandling();

        OutputFormatter::printSeparator(" Demonstration Complete ");
        std::cout << "\n✓ All operations completed successfully!\n\n";
    }

private:
    void createExchange() {
        std::cout << "\n[1] Creating Stock Exchange...\n";
        exchange = std::make_shared<Exchange>();
        std::cout << "    ✓ Exchange created\n";
    }

    void registerStocks() {
        OutputFormatter::printSeparator(" Registering Stocks ");

        appleStock = std::make_shared<Stock>("APPL", "Apple Inc.", 150.00);
        microsoftStock = std::make_shared<Stock>("MSFT", "Microsoft Corporation", 300.00);
        googleStock = std::make_shared<Stock>("GOOGL", "Alphabet Inc.", 2800.00);

        exchange->registerStock(appleStock);
        exchange->registerStock(microsoftStock);
        exchange->registerStock(googleStock);

        std::cout << "✓ Registered 3 stocks:\n";
        for (const auto& stock : exchange->getStocks()) {
            std::cout << "  - " << stock->getSymbol() << ": " << stock->getName()
                      << " (Price: $" << std::fixed << std::setprecision(2)
                      << stock->getCurrentPrice() << ")\n";
        }
    }

    void registerInvestors() {
        OutputFormatter::printSeparator(" Registering Investors ");

        investor1 = std::make_shared<Investor>("Alice Johnson");
        investor2 = std::make_shared<Investor>("Bob Smith");
        investor3 = std::make_shared<Investor>("Charlie Davis");

        exchange->registerInvestor(investor1);
        exchange->registerInvestor(investor2);
        exchange->registerInvestor(investor3);

        std::cout << "✓ Registered 3 investors:\n";
        for (const auto& investor : exchange->getInvestors()) {
            std::cout << "  - " << investor->getName() << "\n";
        }
    }

    void subscribeToStocks() {
        OutputFormatter::printSeparator(" Investors Subscribe to Stocks ");

        investor1->subscribe(appleStock);
        investor2->subscribe(appleStock);
        investor3->subscribe(microsoftStock);

        std::cout << "✓ Subscriptions created\n";
    }

    void placeOrders() {
        OutputFormatter::printSeparator(" Placing Orders for Apple Stock ");

        std::cout << "\nAlice places a BUY order: 100 shares at $149.00\n";
        auto order1 = investor1->placeOrder(appleStock, 100, OrderType::BUY, 149.00);

        std::cout << "Bob places a SELL order: 50 shares at $150.00\n";
        auto order2 = investor2->placeOrder(appleStock, 50, OrderType::SELL, 150.00);

        std::cout << "\n✓ Total orders in Apple stock: " << appleStock->getOrders().size() << "\n";
    }

    void processOrders() {
        OutputFormatter::printSeparator(" Processing Orders for Apple Stock ");

        auto trade = exchange->processOrders(appleStock);

        if (trade.has_value()) {
            std::cout << "✓ Trade executed!\n";
            std::cout << "  - Buy Order: " << trade.value().getBuyOrder()->getInvestorName()
                      << " (" << trade.value().getBuyOrder()->getQuantity() << " shares @ $"
                      << std::fixed << std::setprecision(2) << trade.value().getBuyOrder()->getValue() << ")\n";
            std::cout << "  - Sell Order: " << trade.value().getSellOrder()->getInvestorName()
                      << " (" << trade.value().getSellOrder()->getQuantity() << " shares @ $"
                      << std::fixed << std::setprecision(2) << trade.value().getSellOrder()->getValue() << ")\n";
            std::cout << "  - Executed Quantity: " << trade.value().getExecutedQty() << " shares\n";
            std::cout << "  - Execution Price: $" << std::fixed << std::setprecision(2)
                      << (trade.value().totalValue() / trade.value().getExecutedQty()) << "\n";
            std::cout << "  - Total Value: $" << std::fixed << std::setprecision(2)
                      << trade.value().totalValue() << "\n";
        } else {
            std::cout << "✗ No matching orders found\n";
        }
    }

    void updatePrices() {
        OutputFormatter::printSeparator(" Updating Stock Prices ");

        std::cout << "\nUpdating Apple stock price to $155.00...\n";
        appleStock->updatePrice(155.00);
        std::cout << "✓ Price updated to $" << std::fixed << std::setprecision(2)
                  << appleStock->getCurrentPrice() << "\n";
    }

    void displayPortfolios() {
        OutputFormatter::printSeparator(" Investor Portfolios ");

        OutputFormatter::printPortfolio(investor1->getName(), investor1->getPortfolio());
        OutputFormatter::printPortfolio(investor2->getName(), investor2->getPortfolio());
        OutputFormatter::printPortfolio(investor3->getName(), investor3->getPortfolio());
    }

    void displayMarketData() {
        OutputFormatter::printSeparator(" Market Data ");

        auto marketData = exchange->getMarketData(appleStock);
        if (marketData.has_value()) {
            std::cout << "\nApple Stock Market Data:\n";
            std::cout << "  - Symbol: " << marketData.value().getStock()->getSymbol() << "\n";
            std::cout << "  - Trading Volume: " << marketData.value().getVolume() << " shares\n";
            std::cout << "  - High: $" << std::fixed << std::setprecision(2)
                      << marketData.value().getHigh() << "\n";
            std::cout << "  - Low: $" << std::fixed << std::setprecision(2)
                      << marketData.value().getLow() << "\n";
        }
    }

    void demonstrateErrorHandling() {
        OutputFormatter::printSeparator(" Error Handling Demonstration ");

        try {
            std::cout << "\nAttempting to register duplicate stock (APPL)...\n";
            exchange->registerStock(appleStock);
        } catch (const std::invalid_argument& e) {
            std::cout << "✓ Caught expected error: " << e.what() << "\n";
        }

        try {
            std::cout << "\nAttempting to create invalid order (quantity = 0)...\n";
            auto invalidOrder = std::make_shared<Order>(appleStock, "Test", 0, OrderType::BUY, 100.00);
        } catch (const std::invalid_argument& e) {
            std::cout << "✓ Caught expected error: " << e.what() << "\n";
        }

        try {
            std::cout << "\nAttempting to create investor with empty name...\n";
            auto invalidInvestor = std::make_shared<Investor>("");
        } catch (const std::invalid_argument& e) {
            std::cout << "✓ Caught expected error: " << e.what() << "\n";
        }
    }
};

/**
 * @brief Ponto de entrada principal do programa
 */
int main() {
    try {
        StockExchangeDemonstration demo;
        demo.run();
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
