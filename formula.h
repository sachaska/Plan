#ifndef FORMULA_H
#define FORMULA_H

/// Author: Ai Sun
///   Date: 2023, Feb 2
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 *      - 2024, Feb 2 Ai Sun - Delete inner class Material, change the structure
 *      of Formula class.
 */

#include<string>
#include<map>

/// <summary>
/// Class representing a formula.
/// Class Invariant: The quantities of input and output materials must always
/// be non-negative, there must be at least one material, condition and result
/// maps should not be empty, proficiency level remains in the range of [0, 4].
/// </summary>
class Formula
{
private:
    // holds input resource names and corresponding quantities
    std::map<std::string, int> condition;

    // holds output resource names and corresponding quantities
    std::map<std::string, int> result;

    // numbers of produce rate type
    static const int TYPE = 4;

    // produce rate
    const double produceRate[TYPE] = { 0, 0.75, 1, 1.1 };

    // default probability of all produce rate
    double probability[TYPE] = { 0, 25, 45, 95 };

    // holds proficiency level
    int proficiency;

    // default constant value
    const int DEFAULT = 0;

public:
    /// <summary>
    /// Constructor
    /// Precondition: inNames, inQuantities, outNames, outQuantities must not be empty,
    /// inNum and outNum must be non-negative, inQuantities and outQuantities must be positive.
    /// Postcondition: A Formula object is created with given input and output materials.
    /// </summary>
    Formula(const std::string inNames[], const int inQuantities[], int inNum,
            const std::string outNames[], const int outQuantities[], int outNum);

    /// <summary>
    /// Increase function
    /// Precondition: None.
    /// Postcondition: The proficiency level of the Formula object is increased by 1.
    /// </summary>
    void increase();

    /// <summary>
    /// Get Proficiency function
    /// Precondition: None.
    /// Postcondition: The current proficiency level of the Formula object is returned.
    /// </summary>
    int getProficiency() const;

    /// <summary>
    /// Apply function
    /// Precondition: None.
    /// Postcondition: A string representation of the production rate and
    /// simulation result is returned.
    /// </summary>
    std::string apply();

    /// <summary>
    /// To String function
    /// Precondition: None.
    /// Postcondition: A string representation of the Formula object is returned.
    /// </summary>
    std::string toString();

    /// <summary>
    /// Destructor
    /// Precondition: None.
    /// Postcondition: The Formula object is destroyed and its memory is freed.
    /// </summary>
    ~Formula();
};

#endif // !FORMULA_H