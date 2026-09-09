#ifndef OUTPUT_FORMATTER_H
#define OUTPUT_FORMATTER_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include "domain/Portfolio.h"

/**
 * @brief Utilitário para formatação de saída do sistema
 *
 * Responsável por formatar e imprimir informações na saída padrão
 * seguindo um padrão consistente.
 */
class OutputFormatter {
public:
    /**
     * @brief Imprime uma linha separadora com título opcional
     */
    static void printSeparator(const std::string& title = "") {
        std::cout << "\n" << std::string(70, '=');
        if (!title.empty()) {
            std::cout << "\n" << title << "\n" << std::string(70, '=');
        }
        std::cout << "\n";
    }

    /**
     * @brief Imprime as posições de um portfolio
     */
    static void printPortfolio(const std::string& investorName, std::shared_ptr<Portfolio> portfolio) {
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
};

#endif // OUTPUT_FORMATTER_H
