#include "plan.h"
#include "formula.h"
#include "executablePlan.h"
#include "stockpile.h"
#include <iostream>
#include <memory>

std::map<std::string, int> firSupplies = {{"Wood", 100}, {"Iron", 50}};
std::map<std::string, int> secSupplies = {{"Egg", 22}, {"Flour", 1}, {"Sugar", 88}};

const std::string inFirNames[] = {"Wood", "Iron"};
const int inFirQuantities[] = {10, 5};
const std::string outFirNames[] = {"Sword", "Axe"};
const int outFirQuantities[] = {1, 1};

const std::string inSecNames[] = {"Egg", "Flour", "Sugar"};
const int inSecQuantities[] = {3, 10, 8};
const std::string outSecNames[] = {"Cake"};
const int outSecQuantities[] = {1};

void testApply(ExecutablePlan& plan, std::shared_ptr<Stockpile>& stockpile) {
    for (int i = 0; i < 2; ++i) {
        std::cout << "----------BEFORE APPLY----------" << std::endl;
        std::cout << "Current index: " << plan.Query() << std::endl;
        std::cout << "Current stockpile: " << stockpile->query() << std::endl;
        try {
            std::shared_ptr<Stockpile> outputStockpile = plan.Apply(stockpile);
            std::cout << "Applied formula successfully!" << std::endl;
            std::cout << "Resulting Stockpile: ";

            if (outputStockpile->isEmpty()) {
                std::cout << "N/A" << std::endl;
            }
            else
                std::cout << outputStockpile->query() << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Applied formula failed!" << std::endl;
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << "----------AFTER APPLY----------" << std::endl;
        std::cout << "Current index: " << plan.Query() << std::endl;
        std::cout << "Current stockpile: " << stockpile->query() << std::endl;
    }
}

void mainTestApply() {
    std::shared_ptr<Stockpile> firStockpile = std::make_shared<Stockpile>(firSupplies);
    std::shared_ptr<Stockpile> secStockpile = std::make_shared<Stockpile>(secSupplies);

    Formula* firFormula = new Formula(inFirNames, inFirQuantities,
                                      2, outFirNames, outFirQuantities, 2);
    Formula* secFormula = new Formula(inSecNames, inSecQuantities,
                                      3, outSecNames, outSecQuantities, 1);

    ExecutablePlan plan;

    plan.Add(firFormula);
    plan.Add(secFormula);

    testApply(plan, firStockpile);

    delete firFormula;
    delete secFormula;
}

void testStockpileMethods() {
    std::cout << "----------Testing Stockpile Methods----------" << std::endl;
    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>(firSupplies);

    // Test Add method
    stockpile->add("Gold", 10);
    std::cout << "After adding Gold: " << stockpile->query() << std::endl;

    // Test Remove method
    stockpile->remove("Wood");
    std::cout << "After removing Wood: " << stockpile->query() << std::endl;

    try{
        stockpile->remove("inValid");
    } catch (const std::exception& e) {
        std::cout << "Exception captured: " << e.what() << std::endl;
    }

    // Test Query method
    std::cout << "Current stockpile: " << stockpile->query() << std::endl;

    // Test isEmpty method
    std::cout << "Is stockpile empty? " << (stockpile->isEmpty() ? "Yes" : "No") << std::endl;
}

void testExecutablePlanMethods() {
    std::cout << "----------Testing ExecutablePlan Methods----------" << std::endl;
    Formula* firFormula = new Formula(inFirNames, inFirQuantities,
                                      2, outFirNames, outFirQuantities, 2);
    Formula* secFormula = new Formula(inSecNames, inSecQuantities,
                                      3, outSecNames, outSecQuantities, 1);

    ExecutablePlan plan;
    plan.Add(firFormula);
    plan.Add(secFormula);

    // Test Replace method
    plan.Replace(0, secFormula);
    std::cout << "After replacing first formula: " << plan.Query() << std::endl;

    // Test Remove method
    plan.Remove();
    std::cout << "After removing last formula: " << plan.Query() << std::endl;

    // Test Clone method
    ExecutablePlan* clonedPlan = dynamic_cast<ExecutablePlan*>(plan.Clone());
    std::cout << "Cloned plan: " << clonedPlan->Query() << std::endl;
    delete clonedPlan;

    // Test == and != operators
    ExecutablePlan anotherPlan;
    anotherPlan.Add(firFormula);
    std::cout << "Are the two plans equal? " <<
    (plan == anotherPlan ? "Yes" : "No") << std::endl;

    std::cout << "Are the two plans equal? " <<
              (plan != anotherPlan ? "No" : "Yes") << std::endl;

    delete firFormula;
    delete secFormula;
}

int main() {
    mainTestApply();
    return 0;
}