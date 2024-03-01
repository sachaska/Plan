/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */

/*
 * This is the implementation of stockpile.h. The stockpile class represents a
 * collection of resources, each with a certain quantity.
 * The stockpile class provides methods to add a resource with a certain quantity,
 * remove a resource, increase or decrease the quantity of a resource, check if the
 * stockpile is empty, get the current state of the stockpile, and convert a stockpile
 * object to a string.
 *
 * Implementation Invariant:
 * The stockpile class maintains a map where the keys are resource names and the values
 * are their quantities. The quantities of resources must always be non-negative.
 * The stockpile class ensures that the map is properly updated when a resource is added,
 * removed, or its quantity is increased or decreased.
 *
 * Error Processing:
 * The stockpile class throws std::invalid_argument exception if a resource
 * is not found in the stockpile when trying to remove it or decrease its quantity
 * and if the quantity to decrease is greater than the current quantity of the resource.
 *
 * Assumptions:
 * The stockpile class assumes that all resource names passed to its methods are non-empty
 * strings, and that all quantities passed to its methods are non-negative integers.
 * It does not check the validity of resource names or quantities.
 */

#include "stockpile.h"
#include <string>
#include <sstream>
#include <map>
#include <utility>

stockpile::stockpile(std::map<std::string, int> input) {
    supplies = std::move(input);
}

stockpile::stockpile() = default;

stockpile::~stockpile() = default;

bool stockpile::isEmpty() {
    return supplies.size() == DEFAULT;
}

std::map<std::string, int> stockpile::getSupplies() {
    std::map<std::string, int> input = supplies;
    return input;
}

void stockpile::add(const std::string& name, int quantity) {
    supplies[name] = quantity;
}

void stockpile::remove(const std::string & name) {
    if (supplies.find(name) != supplies.end()) {
        supplies.erase(name);
    } else {
        throw std::invalid_argument("Resource not found.");
    }
}

std::string stockpile::query() {
    std::ostringstream os;              // holds string

    // condition to string
    for (auto it = supplies.begin(); it != supplies.end(); ++it) {
        os << it->second << " " << it->first;
        if (std::next(it) != supplies.end())
            os << ", ";
    }

    return os.str();
}

// Method to increase a resource quantity
void stockpile::increase(const std::string& name, int quantity) {
    if (supplies.find(name) != supplies.end()) {
        supplies[name] += quantity;
    } else {
        throw std::invalid_argument("Resource not found.");
    }
}

// Method to decrease a resource quantity
void stockpile::decrease(const std::string& name, int quantity) {
    if (supplies.find(name) != supplies.end()) {
        if (supplies[name] - quantity >= DEFAULT) {
            supplies[name] -= quantity;
        } else {
            throw std::invalid_argument("Not enough quantity to decrease.");
        }
    } else {
        throw std::invalid_argument("Resource not found.");
    }
}
