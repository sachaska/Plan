/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */

/*
 * This is the implementation of Stockpile.h. The Stockpile class represents a
 * collection of resources, each with a certain quantity.
 * The Stockpile class provides methods to add a resource with a certain quantity,
 * remove a resource, increase or decrease the quantity of a resource, check if the
 * Stockpile is empty, get the current state of the Stockpile, and convert a Stockpile
 * object to a string.
 *
 * Implementation Invariant:
 * The Stockpile class maintains a map where the keys are resource names and the values
 * are their quantities. The quantities of resources must always be non-negative.
 * The Stockpile class ensures that the map is properly updated when a resource is added,
 * removed, or its quantity is increased or decreased.
 *
 * Error Processing:
 * The Stockpile class throws std::invalid_argument exception if a resource
 * is not found in the Stockpile when trying to remove it or decrease its quantity
 * and if the quantity to decrease is greater than the current quantity of the resource.
 *
 * Assumptions:
 * The Stockpile class assumes that all resource names passed to its methods are non-empty
 * strings, and that all quantities passed to its methods are non-negative integers.
 * It does not check the validity of resource names or quantities.
 */

#include "stockpile.h"
#include <string>
#include <sstream>
#include <map>
#include <utility>

Stockpile::Stockpile(std::map<std::string, int> input) {
    supplies = std::move(input);
}

Stockpile::Stockpile() = default;

Stockpile::~Stockpile() = default;

bool Stockpile::isEmpty() {
    return static_cast<int>(supplies.size()) == DEFAULT;
}

std::map<std::string, int> Stockpile::getSupplies() {
    std::map<std::string, int> input = supplies;
    return input;
}

void Stockpile::add(const std::string& name, int quantity) {
    supplies[name] = quantity;
}

void Stockpile::remove(const std::string & name) {
    if (supplies.find(name) != supplies.end()) {
        supplies.erase(name);
    } else {
        throw std::invalid_argument("Resource not found.");
    }
}

std::string Stockpile::query() {
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
void Stockpile::increase(const std::string& name, int quantity) {

    if (quantity <= DEFAULT) {
        throw std::invalid_argument("Not valid quantity.");
    }

    if (supplies.find(name) != supplies.end()) {
        supplies[name] += quantity;
    } else {
        throw std::invalid_argument("Resource not found.");
    }

}

// Method to decrease a resource quantity
void Stockpile::decrease(const std::string& name, int quantity) {

    if (quantity <= DEFAULT) {
        throw std::invalid_argument("Not valid quantity.");
    }

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
