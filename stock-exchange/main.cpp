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

/**
 * @brief Imprime uma linha separadora para formatação da saída
 */
void printSeparator(const std::string& title = "") {
    std::cout << "\n" << std::string(70, '=');
    if (!title.empty()) {
        std::cout << "\n" << title << "\n" << std::string(70, '=');
    }
    std::cout << "\n";
}

/**
 * @brief Imprime as posições do portfolio
 */
void printPortfolio(const std::string& investorName, std::shared_ptr<Portfolio> portfolio) {
    std::cout << "\nPortfolio for " << investorName << ":\n";
    const auto& holdings = portfolio->getHoldings();

    if (holdings.empty()) {
        std::cout << "  (empty)\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Stock"
              << std::setw(10) << "Quantity"
              << std::setw(15) << "Current Price"
              << std::setw(20) << "Position Value" << "\n";
    std::cout << std::string(60, '-') << "\n";

    double totalValue = 0.0;
    for (const auto& holding : holdings) {
        auto stock = holding->getStock();
        double positionValue = static_cast<double>(holding->getQuantity()) * stock->getCurrentPrice();

        std::cout << std::left << std::setw(15) << stock->getSymbol()
                  << std::setw(10) << holding->getQuantity()
                  << std::setw(15) << std::fixed << std::setprecision(2) << stock->getCurrentPrice()
                  << std::setw(20) << positionValue << "\n";

        totalValue += positionValue;
    }

    std::cout << std::string(60, '-') << "\n"
              << std::left << std::setw(40) << "Total Portfolio Value:"
              << std::fixed << std::setprecision(2) << totalValue << "\n";
}

int main() {
    try {
        printSeparator(" Stock Exchange System - Demonstration ");

        // ============ 1. Criar a Bolsa ============
        std::cout << "\n[1] Creating Stock Exchange...\n";
        auto exchange = std::make_shared<Exchange>();
        std::cout << "    ✓ Exchange created\n";

        // ============ 2. Registrar Ações ============
        printSeparator(" Registering Stocks ");

        auto appleStock = std::make_shared<Stock>("APPL", "Apple Inc.", 150.00);
        auto microsoftStock = std::make_shared<Stock>("MSFT", "Microsoft Corporation", 300.00);
        auto googleStock = std::make_shared<Stock>("GOOGL", "Alphabet Inc.", 2800.00);

        exchange->registerStock(appleStock);
        exchange->registerStock(microsoftStock);
        exchange->registerStock(googleStock);

        std::cout << "✓ Registered 3 stocks:\n";
        for (const auto& stock : exchange->getStocks()) {
            std::cout << "  - " << stock->getSymbol() << ": " << stock->getName()
                      << " (Price: $" << std::fixed << std::setprecision(2)
                      << stock->getCurrentPrice() << ")\n";
        }

        // ============ 3. Registrar Investidores ============
        printSeparator(" Registering Investors ");

        auto investor1 = std::make_shared<Investor>("Alice Johnson");
        auto investor2 = std::make_shared<Investor>("Bob Smith");
        auto investor3 = std::make_shared<Investor>("Charlie Davis");

        exchange->registerInvestor(investor1);
        exchange->registerInvestor(investor2);
        exchange->registerInvestor(investor3);

        std::cout << "✓ Registered 3 investors:\n";
        for (const auto& investor : exchange->getInvestors()) {
            std::cout << "  - " << investor->getName() << "\n";
        }

        // ============ 4. Inscrever em Ações ============
        printSeparator(" Investors Subscribe to Stocks ");

        investor1->subscribe(appleStock);
        investor2->subscribe(appleStock);
        investor3->subscribe(microsoftStock);

        std::cout << "✓ Subscriptions created\n";

        // ============ 5. Colocar Ordens - Ação Apple ============
        printSeparator(" Placing Orders for Apple Stock ");

        std::cout << "\nAlice places a BUY order: 100 shares at $149.00\n";
        auto order1 = investor1->placeOrder(appleStock, 100, OrderType::BUY, 149.00);

        std::cout << "Bob places a SELL order: 50 shares at $150.00\n";
        auto order2 = investor2->placeOrder(appleStock, 50, OrderType::SELL, 150.00);

        std::cout << "\n✓ Total orders in Apple stock: " << appleStock->getOrders().size() << "\n";

        // ============ 6. Processar Ordens (Match Buy/Sell) ============
        printSeparator(" Processing Orders for Apple Stock ");

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

        // ============ 7. Atualizar Preço ============
        printSeparator(" Updating Stock Prices ");

        std::cout << "\nUpdating Apple stock price to $155.00...\n";
        appleStock->updatePrice(155.00);
        std::cout << "✓ Price updated to $" << std::fixed << std::setprecision(2)
                  << appleStock->getCurrentPrice() << "\n";

        // ============ 8. Verificar Portfolios ============
        printSeparator(" Investor Portfolios ");

        printPortfolio(investor1->getName(), investor1->getPortfolio());
        printPortfolio(investor2->getName(), investor2->getPortfolio());
        printPortfolio(investor3->getName(), investor3->getPortfolio());

        // ============ 9. Dados de Mercado ============
        printSeparator(" Market Data ");

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

        // ============ 10. Demonstração de Tratamento de Erros ============
        printSeparator(" Error Handling Demonstration ");

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

        printSeparator(" Demonstration Complete ");
        std::cout << "\n✓ All operations completed successfully!\n\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}

