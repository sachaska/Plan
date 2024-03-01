//   Author: Ai Sun
//   Date: 2023, Feb 1
//   Platform: CLion (Mac)

// Revision History:
/*      - 2023, Feb 1 Ai Sun - Initial creation of the class.

 *      - 2024, Feb 2 Ai Sun - Delete inner class Material, change the structure
 *      of Formula class.
 *
 *      -2024, Feb 3 Ai Sun - Change arrays to map
 *
 *      -2024, Feb 29 Ai Sun - Add getInput function, change Apply function
 */

/*
 * This is the implementation of formula.h. The Formula class represents a
 * formula that can be used to convert certain input materials into certain output materials.
 * Each Formula object contains two maps, one for the input materials and their
 * quantities, and one for the output materials and their quantities.
 * The Formula class provides methods to increase the proficiency level of a
 * formula, get the current proficiency level, apply the formula to produce
 * output materials, and convert a Formula object to a string.
 *
 * Implementation Invariant:
 * The Formula class maintains two maps, one for the input materials and their
 * quantities, and one for the output materials and their quantities.
 * The quantities of materials must always be non-negative.
 * The Formula class ensures that the maps are properly updated when the
 * proficiency level is increased or the formula is applied.
 *
 * Error Processing:
 * The Formula class checks for errors in its methods and throws
 * exceptions when errors occur. For example, it throws an std::invalid_argument
 * exception if the number of input or output materials is zero, if a material
 * name is empty, or if a material quantity is not a positive integer.
 *
 * Assumptions:
 * The Formula class assumes that all material names passed to its constructor
 * are non-empty strings, and that all material quantities passed to its
 * constructor are positive integers. It does not check the validity of
 * material names or quantities.
 */

#include "formula.h"
#include "stockpile.h"
#include <stdexcept>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

Formula::Formula(const std::string inNames[], const int inQuantities[], int inNum,
                 const std::string outNames[], const int outQuantities[], int outNum)
{
    // Error handle
    if (outNum == DEFAULT || inNum == DEFAULT)
        throw std::invalid_argument
                ("At least one resource should provide.");

    for (int i = DEFAULT; i < inNum; ++i) {
        if (inNames[i].empty())
            throw std::invalid_argument
                    ("resource name shouldn't be empty.");

        if (inQuantities[i] <= DEFAULT)
            throw std::invalid_argument
                    ("resource quantity should be positive integer.");

        condition[inNames[i]] = inQuantities[i];
    }

    for (int i = DEFAULT; i < outNum; ++i) {
        if (outNames[i].empty())
            throw std::invalid_argument
                    ("resource name shouldn't be empty.");

        if (outQuantities[i] <= DEFAULT)
            throw std::invalid_argument
                    ("resource quantity should be positive integer.");

        result[outNames[i]] = outQuantities[i];
    }

    // initialize proficiency level
    proficiency = DEFAULT;

}

bool Formula::operator==(const Formula& other) const {
    // Implement comparison logic here
    // For example, compare condition and result maps
    return (condition == other.condition) && (result == other.result);
}

bool Formula::operator!=(const Formula& other) const {
    // Implement comparison logic here
    return !(*this == other);
}

int Formula::getProficiency() const
{
    return proficiency;
}

void Formula::increase() {
    const int BUFF[] = {0, 5, 6, 3};
    proficiency++;
    
    // change produce rate
    for (int i = DEFAULT; i < TYPE; ++i) {
        probability[(i)] -= BUFF[i];
    }

}

std::string Formula::toString()
{
    std::ostringstream os;              // holds string

    // condition to string
    for (auto it = condition.begin(); it != condition.end(); ++it) {
        os << it->second << " " << it->first;
        if (std::next(it) != condition.end())
            os << ", ";
    }

    os << "-> ";

    // result to string
    for (auto it = result.begin(); it != result.end(); ++it) {
        os << it->second << " " << it->first;
        if (std::next(it) != result.end())
            os << ", ";
    }

    return os.str();
}

stockpile* Formula::applyToStockpile() {

    const int INDEX = 1, MAX = 100;

    double rate;

    stockpile* stock;

    int randomNumber = rand() % MAX;

    for (int i = DEFAULT; i < TYPE; i++) {
        // if is the last one
        if (i == TYPE - INDEX) {

            if (randomNumber >= probability[(i)])
                rate =  produceRate[(i)];

        }
        else if (randomNumber >= probability[(i)] &&
                 randomNumber < probability[(i + INDEX)]) {

            rate =  produceRate[(i)];

        }

    }

    if (rate != 0) {

        std::map<std::string, int> results;

        for (auto & it : result) {

            int temp = it.second;

            results[it.first] = temp * rate;

        }

        stock = new stockpile(results);

    }

    else stock = new stockpile();

    return stock;
}

std::string Formula::apply()
{
    std::ostringstream os;

    const int INDEX = 1, MAX = 100;

    double rate;

    int randomNumber = rand() % MAX;

    for (int i = DEFAULT; i < TYPE; i++) {
        // if is the last one
        if (i == TYPE - INDEX) {

            if (randomNumber >= probability[(i)])
                rate =  produceRate[(i)];

        }
        else if (randomNumber >= probability[(i)] &&
        randomNumber < probability[(i + INDEX)]) {

            rate =  produceRate[(i)];

        }

    }

    std::cout << randomNumber << std::endl;


    os << "PRODUCE RATE: " << rate << std::endl;
    os << "SIMULATION RESULT: ";

    if (rate != 0) {

        // result to string
        for (auto it = result.begin(); it != result.end(); ++it) {

            int temp = it->second;

            os << temp * rate << " " << it->first;

            if (std::next(it) != result.end())
                os << ", ";

        }

    }

    else {
        os << "N/A";
    }

    return os.str();
}

std::map<std::string, int> Formula::getInput() {
    // deep copy a map
    std::map<std::string, int> input = condition;

    return input;
}

Formula::~Formula() = default;