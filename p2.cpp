#include <iostream>
#include "plan.h"
#include "formula.h"
#include <vector>

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

int main() {
    try {
        // Test Formula constructor
        Formula ironBar(ore, oreQty, oreCnt, bar, barQty, barCnt);
        Formula steelBar(oreCoal, oreCoalQty, oreCoalCnt, steel, steelQty, steelCnt);
        Formula plankBrickFormula(woodStone, woodStoneQty, woodStoneCnt, plankBrick, plankBrickQty, plankBrickCnt);
        Formula hydrogenDeuteriumFormula(water, waterQty, waterCnt, hydrogenDeuterium, hydrogenDeuteriumQty, hydrogenDeuteriumCnt);
        Formula cookiesFormula(ingredients, ingredientsQty, ingredientsCnt, cookies, cookiesQty, cookiesCnt);

        std::cout << "----------Test Formula toString----------" << std::endl;
        // Test Formula toString
        std::cout << ironBar.toString() << std::endl;
        std::cout << steelBar.toString() << std::endl;
        std::cout << plankBrickFormula.toString() << std::endl;
        std::cout << hydrogenDeuteriumFormula.toString() << std::endl;
        std::cout << cookiesFormula.toString() << std::endl;

        std::cout << "----------Test Formula apply----------" << std::endl;
        // Test Formula apply
        std::cout << ironBar.apply() << std::endl;
        std::cout << steelBar.apply() << std::endl;
        std::cout << plankBrickFormula.apply() << std::endl;
        std::cout << hydrogenDeuteriumFormula.apply() << std::endl;
        std::cout << cookiesFormula.apply() << std::endl;

        std::cout << "----------Test Plan constructor----------" << std::endl;
        // Test Plan constructor
        Formula* initialSequences[] = {&ironBar, &steelBar};
        Plan plan(initialSequences, 2);
        std::cout << plan.toString() << std::endl;

        std::cout << "----------Test Plan add function----------" << std::endl;
        // Test Plan Add
        plan.Add(&plankBrickFormula);
        plan.Add(&hydrogenDeuteriumFormula);
        plan.Add(&cookiesFormula);
        std::cout << plan.toString() << std::endl;

        std::cout << "----------Test Plan Remove function----------" << std::endl;
        // Test Plan Remove
        plan.Remove();
        std::cout << plan.toString() << std::endl;

        std::cout << "----------Test Plan replace function----------" << std::endl;
        // Test Plan Replace
        plan.Replace(1, &plankBrickFormula);
        std::cout << plan.toString() << std::endl;

        std::cout << "----------Test Plan copy constructor----------" << std::endl;
        // Test Plan copy constructor
        Plan planCopy(plan);
        std::cout << planCopy.toString() << std::endl;

        std::cout << "----------Test Plan move constructor----------" << std::endl;
        // Test Plan move constructor
        Plan planMove(std::move(plan));
        std::cout << planMove.toString() << std::endl;

        std::cout << "----------Test Plan copy operator----------" << std::endl;
        // Test Plan copy assignment operator
        Plan planAssign = planCopy;
        std::cout << planAssign.toString() << std::endl;

        std::cout << "----------Test Plan move operator----------" << std::endl;
        // Test Plan move assignment operator
        Plan planMoveAssign = std::move(planAssign);
        std::cout << planMoveAssign.toString() << std::endl;


    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
