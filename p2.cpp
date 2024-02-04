#include <iostream>
#include "plan.h"
#include "formula.h"
#include <vector>

/// Author: Ai Sun
///   Date: 2023, Feb 2
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the driver.
 */

/*
 * Purpose: This file is used to test the functionality of the Plan class.
 * Input: The input to this program is a set of Formula objects that are used to
 * create and manipulate a Plan object.
 * Process: The program tests each function of the Plan class by creating a Plan
 * object, calling the function, and checking the result.
 * Output: The output of this program is a series of messages that indicate the
 * result of each test.
 */

// 2 iron ore -> 1 iron bar
const std::string ore[] = {"iron ore"};
int oreQty[] = {2};
int oreCnt = 1;

const std::string bar[] = {"iron bar"};
int barQty[] = {1};
int barCnt = 1;

// 3 iron ore, 1 coal -> 1 steel bar
const std::string oreCoal[] = {"iron ore", "coal"};
int oreCoalQty[] = {3, 1};
int oreCoalCnt = 2;

const std::string steel[] = {"steel bar"};
int steelQty[] = {1};
int steelCnt = 1;

// 3 wood, 2 stone -> 2 wooden plank, 1 stone brick
const std::string woodStone[] = {"wood", "stone"};
int woodStoneQty[] = {3, 2};
int woodStoneCnt = 2;

const std::string plankBrick[] = {"wood plank", "stone brick"};
int plankBrickQty[] = {2, 1};
int plankBrickCnt = 2;

// 1000 water -> 999 hydrogen, 1 deuterium
const std::string water[] = {"water"};
int waterQty[] = {1000};
int waterCnt = 1;

const std::string hydrogenDeuterium[] = {"hydrogen", "deuterium"};
int hydrogenDeuteriumQty[] = {999, 1};
int hydrogenDeuteriumCnt = 2;

// 2 butter, 3 egg, 1 sugar, 2 flour, 2 baking soda -> 36 cookies
const std::string ingredients[] = {"butter", "egg", "sugar",
                                   "flour", "baking soda"};
int ingredientsQty[] = {2, 3, 1, 2, 2};
int ingredientsCnt = 5;

const std::string cookies[] = {"cookies"};
int cookiesQty[] = {36};
int cookiesCnt = 1;

// Test Formula constructor
Formula ironBar(ore, oreQty, oreCnt, bar, barQty, barCnt);
Formula steelBar(oreCoal, oreCoalQty, oreCoalCnt, steel, steelQty, steelCnt);
Formula plankBrickFormula(woodStone, woodStoneQty, woodStoneCnt, plankBrick, plankBrickQty, plankBrickCnt);
Formula hydrogenDeuteriumFormula(water, waterQty, waterCnt, hydrogenDeuterium, hydrogenDeuteriumQty, hydrogenDeuteriumCnt);
Formula cookiesFormula(ingredients, ingredientsQty, ingredientsCnt, cookies, cookiesQty, cookiesCnt);

void testPlanConstructor() {
    /*
     * Description: Tests the Plan constructor.
     * Input: None.
     * Modify: Creates a Plan object.
     * Output: Prints a message indicating the result of the test.
     */
    std::cout << "----------Test Plan constructor----------" << std::endl;
    // Test Plan constructor
    Plan plan;
    std::cout << "An empty plan instance has create." << std::endl;
}

void testPlanAdd() {
    /*
    * Description: Tests the Plan Add function.
    * Input: A Formula object to be added to the Plan.
    * Modify: Adds a Formula object to the Plan.
    * Output: Prints a message indicating the result of the test.
    */
    std::cout << "----------Test Plan add function----------" << std::endl;
    // Test Plan Add
    int size = 2;
    Formula* initialSequences[] = {&ironBar, &steelBar};
    Plan plan(initialSequences, size);
    std::cout << "Before add:" << std::endl;
    std::cout << plan.toString() << std::endl;

    std::cout << "Adding Plank Brick Formula..." << std::endl;
    plan.Add(&plankBrickFormula);
    std::cout << plan.toString() << std::endl;

    std::cout << "Adding hydrogen Deuterium Formula..." << std::endl;
    plan.Add(&hydrogenDeuteriumFormula);
    std::cout << plan.toString() << std::endl;

    std::cout << "Adding cookies Formula..." << std::endl;
    plan.Add(&cookiesFormula);
    std::cout << plan.toString() << std::endl;
}

void testPlanReplace() {
    /*
     * Description: Tests the Plan Replace function.
     * Input: An index and a Formula object to replace the existing Formula at the index in the Plan.
     * Modify: Replaces a Formula object in the Plan.
     * Output: Prints a message indicating the result of the test.
     */
    std::cout << "----------Test Plan replace function----------" << std::endl;
    int size = 2, replace = 1;
    std::cout << "Before replace:" << std::endl;
    Formula* initialSequences[] = {&ironBar, &steelBar};
    Plan plan(initialSequences, size);
    std::cout << plan.toString() << std::endl;
    std::cout << "After replace (index 1, number 2): "
                 "\n\t\tsteel bar --replace--> cookies" << std::endl;
    // Test Plan Replace with valid index
    plan.Replace(replace, &cookiesFormula);
    std::cout << plan.toString() << std::endl;

    // Test Plan Replace with invalid index
    try {
        plan.Replace(-1, &cookiesFormula);
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        plan.Replace(size, &cookiesFormula);
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void testPlanRemove() {
    /*
        * Description: Tests the Remove function of the Plan class.
        * Input: None.
        * Modify: Creates a Plan object, removes Formulas until all
        * are removed, and attempts to remove from an empty Plan to trigger an exception.
        * Output: Prints the state of the Plan object after each
        * removal and the exception message when trying to remove from an empty Plan.
        */
    std::cout << "----------Test Plan Remove function----------" << std::endl;
    int size = 2;
    Formula* initialSequences[] = {&ironBar, &steelBar};
    Plan plan(initialSequences, size);
    std::cout << "Before remove:" << std::endl;
    std::cout << plan.toString() << std::endl;

    std::cout << "After remove:" << std::endl;
    // Test Plan Remove
    plan.Remove();
    std::cout << plan.toString() << std::endl;

    // Test Plan Remove until all sequences are removed
    for (int i = 0; i < size - 1; ++i) {
        plan.Remove();
    }

    // Test Plan Remove to trigger an exception
    try {
        plan.Remove();
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void testPlanCopyConstructor() {
    /*
    * Description: Tests the Plan copy constructor.
    * Input: A Plan object to be copied.
    * Modify: Creates a new Plan object as a copy of the input Plan.
    * Output: Prints a message indicating the result of the test.
    */
    std::cout << "----------Test Plan copy constructor----------" << std::endl;
    int size = 2;
    Formula* initialSequences[] = {&ironBar, &steelBar};
    Plan plan(initialSequences, size);
    // Test Plan copy constructor
    Plan planCopy(plan);
    std::cout << planCopy.toString() << std::endl;
}

void testPlanMoveConstructor() {
    /*
     * Description: Tests the move constructor of the Plan class.
     * Input: None.
     * Modify: Creates a Plan object and then a new Plan object by
     * moving the first one.
     * Output: Prints the state of the new Plan object.
     */
    std::cout << "----------Test Plan move constructor----------" << std::endl;
    // Test Plan move constructor
    int size = 2;
    Formula* initialSequences[] = {&ironBar, &steelBar};
    Plan plan(initialSequences, size);
    Plan planMove(std::move(plan));
    std::cout << planMove.toString() << std::endl;
}

void testPlanCopyOperator() {
    /*
    * Description: Tests the Plan copy assignment operator.
    * Input: A Plan object to be copied.
    * Modify: Assigns the current Plan object as a copy of the input Plan.
    * Output: Prints a message indicating the result of the test.
    */
    std::cout << "----------Test Plan copy operator----------" << std::endl;
    // Test Plan copy assignment operator
    int size = 3;
    Formula* initialSequences[] = {&hydrogenDeuteriumFormula, &ironBar, &steelBar};
    Plan planCopy(initialSequences, size);
    Plan planAssign = planCopy;
    std::cout << planAssign.toString() << std::endl;
}

void testPlanMoveOperator() {
    /*
      * Description: Tests the Plan move assignment operator.
      * Input: A Plan object to be moved.
      * Modify: Assigns the current Plan object by moving the input Plan.
      * Output: Prints a message indicating the result of the test.
      */
    std::cout << "----------Test Plan move operator----------" << std::endl;
    Formula* initialSequences[] = {&hydrogenDeuteriumFormula, &ironBar, &steelBar};
    int size = 3;
    Plan planAssign(initialSequences, size);
    // Test Plan move assignment operator
    Plan planMoveAssign = std::move(planAssign);
    std::cout << planMoveAssign.toString() << std::endl;
}

void testPlanException() {
    /*
     * Description: Tests the Plan constructor for exception handling.
     * Input: None.
     * Modify: Attempts to create a Plan object with invalid parameters.
     * Output: Prints a message indicating whether the correct exception was thrown.
     */
    std::cout << "----------Test Plan constructor exception----------" << std::endl;
    // Test Plan constructor exception
    try {
        int size = 0;
        Formula* initialSequences[] = {&ironBar, &steelBar};
        Plan plan(initialSequences, size);
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    testPlanConstructor();
    testPlanAdd();
    testPlanRemove();
    testPlanReplace();
    testPlanCopyConstructor();
    testPlanMoveConstructor();
    testPlanCopyOperator();
    testPlanMoveOperator();
    testPlanException();

    return 0;
}