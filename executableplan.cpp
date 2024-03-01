#include "executableplan.h"
#include <stdexcept>
#include <iostream>

/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 29 Ai Sun - Initial creation of the class.
 */

/*
 * This is the implementation of ExecutablePlan.h. The ExecutablePlan class is a
 * derived class of Plan that represents a plan that contains a dynamic array of
 * Formula objects and maintains a current index to keep track of the progress of the plan.
 * Each Formula object represents a formula that can be used to convert certain
 * input materials into certain output materials.
 * The ExecutablePlan class provides methods to apply the current formula, query
 * the current formula, replace a formula at a specific index in the plan,
 * remove the last formula from the plan, and clone the current plan. It also
 * provides methods to create a deep copy of an ExecutablePlan object,
 * and convert an ExecutablePlan object to a string.
 *
 * Implementation Invariant:
 * The ExecutablePlan class maintains a dynamic array of Formula objects, represented
 * as a double pointer to Formula, and a current index to keep track of the progress of the plan.
 * The size of the dynamic array is always non-negative, and the capacity of
 * the dynamic array is always greater than or equal to the size.
 * The ExecutablePlan class ensures that the dynamic array is properly resized
 * when a new Formula is added and there is no more space left in the array.
 * It also ensures that the dynamic array and all Formula objects it contains
 * are properly deleted when an ExecutablePlan object is destroyed.
 *
 * Error Processing:
 * The ExecutablePlan class checks for errors in its methods and throws
 * exceptions when errors occur. For example, it throws an std::out_of_range exception
 * if the Apply method is called when the current index is beyond the end of
 * the sequence, an std::invalid_argument exception if the Replace method is called
 * with an index that is less than the current index, and an std::out_of_range
 * exception if the Remove method is called when the size of the dynamic array
 * is less than or equal to the current index.
 *
 * Assumptions:
 * The ExecutablePlan class assumes that all Formula objects passed to its
 * methods are valid. It does not check the validity of Formula objects.
 * It also assumes that the index passed to the Replace method is a valid
 * index in the dynamic array. It does not check the validity of the index.
 */

// Constructor
ExecutablePlan::ExecutablePlan(Formula* initialSequences[], int initialSize) :
Plan(initialSequences, initialSize), current(DEFAULT) {}

// Method to apply the current formula
std::string ExecutablePlan::Apply() {

    if (current >= size) {
        throw std::out_of_range
        ("Cannot advance beyond the end of the sequence.");
    }

    current++;

    return sequences[current - INDEX]->apply();
}

std::shared_ptr<Stockpile> ExecutablePlan::Apply(const std::shared_ptr<Stockpile>& stock) {

    if (current >= size) {
        throw std::out_of_range("Cannot advance beyond the end of the sequence.");
    }

    std::map<std::string, int> supplies = stock->getSupplies();
    std::map<std::string, int> inputs = sequences[current]->getInput();

    // If the sizes of the inputs and supplies maps are not equal, throw an exception
    if (inputs.size() != supplies.size()) {
        throw std::invalid_argument("The sizes are not equal.");
    }

    for (const auto& input : inputs) {
        // If the key in the inputs map does not exist in the supplies map, throw an exception
        if (supplies.find(input.first) == supplies.end()) {
            throw std::invalid_argument("The names are not equal.");
        }

        // If quantity in stockpile is not enough, throw an exception
        if (supplies[input.first] < input.second) {
            throw std::invalid_argument("Not enough supplies in the current Stockpile.");
        }
    }

    // If not, remove the associated quantities from Stockpile.
    for (const auto& input : inputs) {
        stock->decrease(input.first, input.second);
    }

    // Return a smart pointer to new Stockpile, containing result
    std::shared_ptr<Stockpile> result(sequences[current]->applyToStockpile());

    // Update current index
    current++;

    // Return the smart pointer to the new Stockpile
    return result;
}

// Method to query the current formula
std::string ExecutablePlan::Query() {
    return "(" +std::to_string(current + INDEX) + "). " +
    sequences[current]->toString();
}

// Method to replace a formula in the Plan
void ExecutablePlan::Replace(int index, Formula* newFormula) {

    if (index < current) {
        throw std::invalid_argument("Cannot edit a completed step.");
    }

    Plan::Replace(index, newFormula);
}

// Method to remove the last formula in the Plan
void ExecutablePlan::Remove() {

    if (size - INDEX < current) {
        throw std::out_of_range("Cannot remove a completed step.");
    }

    Plan::Remove();
}

// Method to clone the current plan
Plan* ExecutablePlan::Clone() {
    ExecutablePlan* newPlan = new ExecutablePlan(sequences, size);
    newPlan->current = current;
    return newPlan;
}

bool ExecutablePlan::operator==(const ExecutablePlan& other) const {
    return (current == other.current)
    && (static_cast<const Plan&>(*this) == static_cast<const Plan&>(other));
}

bool ExecutablePlan::operator!=(const ExecutablePlan& other) const {
    return !(*this == other);
}
