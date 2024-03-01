#include "executablePlan.h"
#include <stdexcept>
#include <iostream>

/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 29 Ai Sun - Initial creation of the class.
 */

/*
 * This is the implementation of executablePlan.h. The executablePlan class is a
 * derived class of Plan that represents a plan that contains a dynamic array of
 * Formula objects and maintains a current index to keep track of the progress of the plan.
 * Each Formula object represents a formula that can be used to convert certain
 * input materials into certain output materials.
 * The executablePlan class provides methods to apply the current formula, query
 * the current formula, replace a formula at a specific index in the plan,
 * remove the last formula from the plan, and clone the current plan. It also
 * provides methods to create a deep copy of an executablePlan object,
 * and convert an executablePlan object to a string.
 *
 * Implementation Invariant:
 * The executablePlan class maintains a dynamic array of Formula objects, represented
 * as a double pointer to Formula, and a current index to keep track of the progress of the plan.
 * The size of the dynamic array is always non-negative, and the capacity of
 * the dynamic array is always greater than or equal to the size.
 * The executablePlan class ensures that the dynamic array is properly resized
 * when a new Formula is added and there is no more space left in the array.
 * It also ensures that the dynamic array and all Formula objects it contains
 * are properly deleted when an executablePlan object is destroyed.
 *
 * Error Processing:
 * The executablePlan class checks for errors in its methods and throws
 * exceptions when errors occur. For example, it throws an std::out_of_range exception
 * if the Apply method is called when the current index is beyond the end of
 * the sequence, an std::invalid_argument exception if the Replace method is called
 * with an index that is less than the current index, and an std::out_of_range
 * exception if the Remove method is called when the size of the dynamic array
 * is less than or equal to the current index.
 *
 * Assumptions:
 * The executablePlan class assumes that all Formula objects passed to its
 * methods are valid. It does not check the validity of Formula objects.
 * It also assumes that the index passed to the Replace method is a valid
 * index in the dynamic array. It does not check the validity of the index.
 */

// Constructor
executablePlan::executablePlan(Formula* initialSequences[], int initialSize) :
Plan(initialSequences, initialSize), current(DEFAULT) {}

// Method to apply the current formula
std::string executablePlan::Apply() {

    if (current >= size) {
        throw std::out_of_range
        ("Cannot advance beyond the end of the sequence.");
    }

    current++;

    return sequences[current - INDEX]->apply();
}

std::shared_ptr<stockpile> executablePlan::Apply
(const std::shared_ptr<stockpile>& stock) {

    if (current >= size) {
        throw std::out_of_range
                ("Cannot advance beyond the end of the sequence.");
    }

    std::map<std::string, int> supplies = stock->getSupplies();

    std::map<std::string, int> inputs = sequences[current]->getInput();

    for (const auto& input : inputs) {

        if (supplies[input.first] < input.second) {
            throw std::invalid_argument("Not enough supplies in "
                                        "the current stockpile.");
        }

    }

    // If not, remove the associated quantities from stockpile.
    for (const auto& input : inputs) {
        stock->decrease(input.first, input.second);
    }

    // Return a smart pointer to new stockpile, containing result
    std::shared_ptr<stockpile> result(sequences[current]->applyToStockpile());

    // Update current index
    current++;

    // Return the smart pointer to the new stockpile
    return result;
}

// Method to query the current formula
std::string executablePlan::Query() {
    return "(" +std::to_string(current + INDEX) + "). " +
    sequences[current]->toString();
}

// Method to replace a formula in the Plan
void executablePlan::Replace(int index, Formula* newFormula) {

    if (index < current) {
        throw std::invalid_argument("Cannot edit a completed step.");
    }

    Plan::Replace(index, newFormula);
}

// Method to remove the last formula in the Plan
void executablePlan::Remove() {

    if (size - INDEX < current) {
        throw std::out_of_range("Cannot remove a completed step.");
    }

    Plan::Remove();
}

// Method to clone the current plan
Plan* executablePlan::Clone() {
    executablePlan* newPlan = new executablePlan(sequences, size);
    newPlan->current = current;
    return newPlan;
}

bool executablePlan::operator==(const executablePlan& other) const {
    return (current == other.current)
    && (static_cast<const Plan&>(*this) == static_cast<const Plan&>(other));
}

bool executablePlan::operator!=(const executablePlan& other) const {
    return !(*this == other);
}
