#include "plan.h"
#include "formula.h"
#include "executableplan.h"
#include "stockpile.h"
#include <iostream>
#include <memory>

/// Author: Ai Sun
///   Date: 2023, Feb 2
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the driver.
 */

/*
 * Purpose: This file is used to test the functionality of new methods in Plan
 * and Formula, complete functions of Stockpile, and ExecutablePlan classes.
 *
 * Input: The input to this program is a set of Formula objects that are used
 * to create and manipulate a Plan object.
 *
 * Process: The program tests each function of the Plan, Formula, Stockpile,
 * and ExecutablePlan classes by creating objects, calling the function, and
 * checking the result.
 *
 * Output: The output of this program is a series of messages that indicate
 * the result of each test.
 */

// Global variables for testing
std::map<std::string, int> firSupplies = {{"Wood", 100}, {"Iron", 50}};
std::map<std::string, int> secSupplies = {{"Egg", 22}, {"Flour", 1},
                                          {"Sugar", 88}};

const std::string inFirNames[] = {"Wood", "Iron"};
const int inFirQuantities[] = {10, 5};
const std::string outFirNames[] = {"Sword", "Axe"};
const int outFirQuantities[] = {1, 1};

const std::string inSecNames[] = {"Egg", "Flour", "Sugar"};
const int inSecQuantities[] = {3, 10, 8};
const std::string outSecNames[] = {"Cake"};
const int outSecQuantities[] = {1};

/*
 * Description: Tests the methods of the Formula class.
 * Input: None.
 * Modify: Creates Formula objects and performs operations on them.
 * Output: Prints a message indicating the result of each test.
 */
void testFormulaMethods();

/*
 * Description: Tests the constructors of the Plan class.
 * Input: None.
 * Modify: Creates Plan objects.
 * Output: Prints a message indicating the result of the test.
 */
void testPlanConstructors();

/*
 * Description: Tests the operators of the Plan class.
 * Input: None.
 * Modify: Creates Plan objects and performs operations on them.
 * Output: Prints a message indicating the result of the test.
 */
void testPlanOperators();

/*
 * Description: Tests the Apply function of the ExecutablePlan class.
 * Input: An ExecutablePlan object and a shared pointer to a Stockpile object.
 * Modify: Applies the plan to the stockpile.
 * Output: Prints a message indicating the result of the test.
 */
void mainTestApply();

/*
 * Description: Tests the methods of the Stockpile class.
 * Input: None.
 * Modify: Creates a Stockpile object and performs operations on it.
 * Output: Prints a message indicating the result of the test.
 */
void testStockpileMethods();

/*
 * Description: Tests the methods of the ExecutablePlan class.
 * Input: None.
 * Modify: Creates an ExecutablePlan object and performs operations on it.
 * Output: Prints a message indicating the result of the test.
 */
void testExecutablePlanMethods();

void testFormulaMethods() {
    std::cout << "----------Testing Formula Methods----------" << std::endl;
    const std::string inNames[] = {"Iron", "Gold"};
    const int inQuantities[] = {10, 20};
    const std::string outNames[] = {"Silver", "Copper"};
    const int outQuantities[] = {30, 40};

    Formula* firFormula = new Formula(inNames, inQuantities,
                                      2, outNames, outQuantities, 2);
    Formula* secFormula = new Formula(inNames, inQuantities,
                                      2, outNames, outQuantities, 2);

    // Test == and != operators
    std::cout << "Are the two formulas equal? " <<
              (*firFormula == *secFormula ? "Yes" : "No") << std::endl;

    std::cout << "Are the two formulas not equal? " <<
              (*firFormula != *secFormula ? "Yes" : "No") << std::endl;

    // Test getInput function
    std::map<std::string, int> inputs = firFormula->getInput();
    std::cout << "Inputs of the first formula: " << std::endl;
    for (const auto& pair : inputs) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Test ApplyToStockpile function
    std::cout << "ApplyToStockpile function will be test "
                 "indirect in executablePlan class." << std::endl;

    delete firFormula;
    delete secFormula;
}

void testPlanConstructors() {
    std::cout << "----------Testing Plan Constructors----------" << std::endl;
    Formula* firFormula = new Formula(inFirNames, inFirQuantities,
                                      2, outFirNames, outFirQuantities, 2);
    Formula* secFormula = new Formula(inSecNames, inSecQuantities,
                                      3, outSecNames, outSecQuantities, 1);

    Plan plan;
    plan.Add(firFormula);
    plan.Add(secFormula);

    // Test Copy constructor
    Plan copiedPlan = plan;
    std::cout << "Copied plan: " << copiedPlan << std::endl;
    std::cout << "Does copied plan as same as original plan?"
    << (plan < copiedPlan ? "Yes" : "No") << std::endl;

    // Test Move constructor
    Plan movedPlan = std::move(copiedPlan);
    std::cout << "Moved plan: " << movedPlan << std::endl;

    std::cout << "Does original plan still exist?"
              << (copiedPlan == nullptr ? "No" : "Yes") << std::endl;

    delete firFormula;
    delete secFormula;
}

void testPlanOperators() {
    std::cout << "----------Testing Plan Operators----------" << std::endl;
    Formula* firFormula = new Formula(inFirNames, inFirQuantities,
                                      2, outFirNames, outFirQuantities, 2);
    Formula* secFormula = new Formula(inSecNames, inSecQuantities,
                                      3, outSecNames, outSecQuantities, 1);

    Plan plan;
    plan.Add(firFormula);
    plan.Add(secFormula);

    // Test == and != operators
    Plan anotherPlan;
    anotherPlan.Add(firFormula);
    anotherPlan.Add(secFormula);

    std::cout << "Are the two plans equal? " <<
              (plan == anotherPlan ? "Yes" : "No") << std::endl;

    std::cout << "Are the two plans not equal? " <<
              (plan != anotherPlan ? "Yes" : "No") << std::endl;

    // Test < and > operators
    std::cout << "Is the first plan's size smaller than the second plan? " <<
              (plan < anotherPlan ? "Yes" : "No") << std::endl;

    std::cout << "Is the first plan's size bigger than the second plan? " <<
              (plan > anotherPlan ? "Yes" : "No") << std::endl;

    // Test << operator
    std::cout << "First plan: " << plan << std::endl;
    std::cout << "Second plan: " << anotherPlan << std::endl;

    delete firFormula;
    delete secFormula;
}


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

    // Test Decrease method
    stockpile->decrease("Iron", 10);
    std::cout << "After decreasing Iron: " << stockpile->query() << std::endl;

    int invalid_value = 100;
    std::string invalid_name = "SJ";
    int zero = 0;

    try{
        stockpile->decrease("Iron", invalid_value);
    } catch (const std::exception& e) {
        std::cout << "Exception captured: " << e.what() << std::endl;
    }

    try{
        stockpile->decrease("Iron", zero);
    } catch (const std::exception& e) {
        std::cout << "Exception captured: " << e.what() << std::endl;
    }

    try{
        stockpile->decrease(invalid_name, 10);
    } catch (const std::exception& e) {
        std::cout << "Exception captured: " << e.what() << std::endl;
    }

    // Test Increase method
    stockpile->increase("Iron", 20);
    std::cout << "After increasing Iron: " << stockpile->query() << std::endl;

    try{
        stockpile->increase(invalid_name, 10);
    } catch (const std::exception& e) {
        std::cout << "Exception captured: " << e.what() << std::endl;
    }

    try{
        stockpile->increase("Iron", zero);
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

    // Copy constructor
    ExecutablePlan samePlan = plan;

    anotherPlan.Add(firFormula);
    anotherPlan.Add(secFormula);

    std::cout << "Are deepcopy same plan equal to original? " <<
              (plan == samePlan ? "Yes" : "No") << std::endl;

    std::cout << "Are the two plans equal? " <<
    (plan == anotherPlan ? "Yes" : "No") << std::endl;

    std::cout << "Are the two plans not equal? " <<
              (plan != anotherPlan ? "Yes" : "No") << std::endl;

    // Test < and > operators
    std::cout << "Is the first plan's size smaller than the second plan? " <<
              (plan < anotherPlan ? "Yes" : "No") << std::endl;

    std::cout << "Is the first plan's size bigger than the second plan? " <<
              (plan > anotherPlan ? "Yes" : "No") << std::endl;

    // Test << operator
    std::cout << "First plan: " << plan << std::endl;
    std::cout << "Second plan: " << anotherPlan << std::endl;

    delete firFormula;
    delete secFormula;
}

int main() {
    testFormulaMethods();
    testPlanConstructors();
    testPlanOperators();
    mainTestApply();
    testStockpileMethods();
    testExecutablePlanMethods();
    return 0;
}