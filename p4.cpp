#include "plan.h"
#include "formula.h"
#include "executablePlan.h"
#include "stockpile.h"
#include <iostream>
#include <memory>

int main() {
    std::map<std::string, int> inputSupplies = {{"Wood", 100}, {"Iron", 50}};
    std::shared_ptr<Stockpile> inputStockpile = std::make_shared<Stockpile>(inputSupplies);

    const std::string inNames[] = {"Wood", "Iron"};
    const int inQuantities[] = {10, 5};
    const std::string outNames[] = {"Sword"};
    const int outQuantities[] = {1};
    Formula* formula = new Formula(inNames, inQuantities, 2, outNames, outQuantities, 1);

    ExecutablePlan plan;
    plan.Add(formula);

    try {
        std::shared_ptr<Stockpile> outputStockpile = plan.Apply(inputStockpile);
        std::cout << "Applied formula successfully!" << std::endl;
        std::cout << "Resulting Stockpile: ";

        if (outputStockpile->isEmpty()) {
            std::cout << "N?A" << std::endl;
        }
        else
            std::cout << outputStockpile->query() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    delete formula;

    return 0;
}
