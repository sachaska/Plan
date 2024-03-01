//
// Created by Sun Ai on 2024/2/28.
//
#include "executablePlan.h"
#include "stockpile.h"
#include <iostream>
#include <memory>

int main() {
    std::map<std::string, int> inputSupplies = {{"Wood", 100}, {"Iron", 50}};
    std::shared_ptr<stockpile> inputStockpile = std::make_shared<stockpile>(inputSupplies);

    const std::string inNames[] = {"Wood", "Iron"};
    const int inQuantities[] = {10, 5};
    const std::string outNames[] = {"Sword"};
    const int outQuantities[] = {1};
    Formula* formula = new Formula(inNames, inQuantities, 2, outNames, outQuantities, 1);

    executablePlan plan;
    plan.Add(formula);

    try {
        std::shared_ptr<stockpile> outputStockpile = plan.Apply(inputStockpile);
        std::cout << "Applied formula successfully!" << std::endl;
        std::cout << "Resulting stockpile: ";

        if (outputStockpile->isEmpty()) {
            std::cout << "N?A" << std::endl;
        }
        else
            std::cout << outputStockpile->query() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 释放 Formula 对象的内存
    delete formula;

    return 0;
}
