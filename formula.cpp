//   Author: Ai Sun
//   Date: 2023, Feb 1
//   Platform: CLion (Mac)

// Revision History:
/*      - 2023, Feb 1 Ai Sun - Initial creation of the class.
 */

// Process:
/*      A Formula object is created by the user inputting material names and
 *      quantities (both input and output materials) through the constructor,
 *      which initializes the _inputMaterials and _outputMaterials.
 *
 *      For each material, the constructor checks if the provided quantity is
 *      greater than zero, and creates a new Material instance.
 *
 *      Upon stored relationship (_inputMaterials and _outputMaterials),
 *      it calculates the conversion probabilities and potential output
 *      materials based on the stored manufacturing probabilities
 *      (_probability array) and efficiencies (_produceRate array).
 *
 *      The user can interact further with the instance of Formula by calling
 *      the other methods to check or set the current proficiency level,
 *      or retrieve the list of materials for conversion.
 */

// Assumptions:
/*      1. The input and output material names provided by the user should not
 *      be null or empty.
 *
 *      2. The quantities of input and output materials provided should always
 *      be positive.
 *
 *      3. The _produceRate and _probability arrays are always of length 4.
 *
 *      4. Proficiency should always be integer,
 *      in the range of 0 to 4 (include 4).
 */

// Use and Validity (Error Processing):
/*      The Formula class validates its input in several ways:
 *          - If input name is empty, an exception is thrown.
 *
 *          - If input quantity is empty, an exception is thrown.
 *
 *          - If the input names' length does not match their respective
 *          quantities, an exception is thrown.
 *
 *          - If the input name does not match as in the format,
 *          an exception is thrown.
 *
 *          - If any input or output quantity is less than zero,
 *          an exception is thrown.
 *
 *          - These checks ensure the validity of the Formula object
 *          throughout its lifecycle.
 */

#include "formula.h"
#include <stdexcept>
#include <string>
#include <sstream>

const std::string Formula::EMPTY_STR;

Formula::Material::Material(std::string inName, int quantity)
{
    if (inName.empty())
        throw std::invalid_argument
                ("Name should not be empty.");
    if (quantity <= 0)
        throw std::invalid_argument
                ("Name should not be empty.");
    name = inName;
    this->quantity = quantity;
}

Formula::Material::Material():name(EMPTY_STR), quantity(DEFAULT) {}

Formula::Material::Material(const Material& other)
{
    name = other.name;
    quantity = other.quantity;
}

std::string Formula::Material::getName()
{
    return name;
}

int Formula::Material::getQuantity() const
{
    return quantity;
}

std::string Formula::Material::toString()
{
    std::ostringstream os;
    os << quantity << " " << name;
    return os.str();
}

Formula::Formula(const std::string inNames[], int inQuantities[],
                 int inCount,
                 const std::string outNames[], int outQuantities[],
                 int outCount)
{
    if (outCount == 0 || inCount == 0)
        throw std::invalid_argument
                ("At least one resource should provide.");

    // If size of inNames and inQuantities not match, throw exception
    inSize = inCount;
    outSize = outCount;

    // Initialize inputMaterials and outputMaterials
    inputMaterials = new Material[inSize];
    outputMaterials = new Material[outSize];

    try {
        for (int i = 0; i < inSize; i++) {
            inputMaterials[i] = Material(inNames[i],
                                         inQuantities[i]);
        }

        for (int i = 0; i < outSize; i++) {
            outputMaterials[i] = Material(outNames[i],
                                          outQuantities[i]);
        }

    } catch (std::exception &e) {
        throw std::invalid_argument
        ("Numbers of names and quantity not match");
    }

    // initialize proficiency level
    proficiency = 0;

    // initialize current probability
    for (int i = 0; i < 4; i++) {
        currentProbability[i] = probability[i];
    }
}


void Formula::updateProbability(int val)
{
    int change = 5 * val;
    currentProbability[0] -= change;
    currentProbability[1] -= change;
    currentProbability[2] += change;
    currentProbability[3] += change;
}

double Formula::produce()
{
    int randomNumber = rand() % 100;
    for (int i = 3; i >= 0; --i) {
        if (randomNumber >= currentProbability[i]) {
            return produceRate[i];
        }
    }

    return 0;
}

int Formula::getProficiency() const
{
    return proficiency;
}

void Formula::setProficiency(int level)
{
    if (level < 0 || level > 4) {
        throw std::invalid_argument("Invalid proficiency level.");
    }

    updateProbability(level - proficiency);
    proficiency = level;
}

std::string Formula::toString()
{
    std::ostringstream os;
    for (int i = 0; i < (int)inSize; i++) {
        if (i != 0)
            os << ", ";
        os << inputMaterials[i].toString();
    }
    os << "-> ";
    for (int i = 0; i < (int)outSize; i++) {
        if (i != 0)
            os << ", ";
        os << outputMaterials[i].toString();
    }
    return os.str();
}

std::string Formula::apply()
{
    std::ostringstream os;
    double rate = produce();
    os << "PRODUCE RATE: " << rate << std::endl;
    os << "SIMULATION RESULT: ";
    if (rate != 0) {
        for (int i = 0; i < (int)outSize; i++) {
            os << outputMaterials[i].getQuantity() * rate
            << " " << outputMaterials[i].getName() << ", ";
        }
    }
    else {
        os << "N/A";
    }
    return os.str();
}

Formula::~Formula() {
    if (inputMaterials != nullptr) {
        delete[] inputMaterials;
        inputMaterials = nullptr;
    }
    if (outputMaterials != nullptr) {
        delete[] outputMaterials;
        outputMaterials = nullptr;
    }
}