// Author: Ai Sun
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

#ifndef FORMULA_H
#define FORMULA_H

#include<string>

/// <summary>
/// Class representing a formula.
/// Class Invariant: The quantities of input and output materials must always
/// be non-negative,
///                   and there must be at least one output material.
/// </summary>
class Formula
{
private:
    /// <summary>
    /// Class representing a material.
    /// Class Invariant: Name and quantity shouldn't be null.
    /// quantity must always be non-negative.
    /// </summary>
    class Material
    {
    private:
        std::string name;

        int quantity;

    public:
        Material(std::string name, int quantity);

        Material();

        Material(const Material& other);

        std::string getName();

        int getQuantity() const;

        std::string toString();
    };

    double produceRate[4] = { 0, 0.75, 1, 1.1 };

    double probability[4] = { 25, 45, 95, 100 };

    double currentProbability[4]{};

    Material* inputMaterials;

    Material* outputMaterials;

    int proficiency;

    int inSize, outSize;                        // number of input names
                                                // number of output names

    void updateProbability(int val);

    double produce();

public:
    Formula(const std::string inNames[], int inQuantities[], int inCount,
            const std::string outNames[], int outQuantities[], int outCount);

    int getProficiency() const;

    void setProficiency(int level);

    std::string apply();

    std::string toString();

    static int const DEFAULT = 0;

    static std::string const EMPTY_STR;

    ~Formula();
};

#endif // !FORMULA_H
