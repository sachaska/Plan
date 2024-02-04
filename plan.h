#ifndef PLAN_H
#define PLAN_H

#include "formula.h"

/// Author: Ai Sun
///   Date: 2023, Feb 2
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */

/// <summary>
/// Class representing a plan.
/// Class Invariant: The size of the dynamic array must always be non-negative,
/// and the capacity of the dynamic array must always be greater than or equal
/// to the size.
/// </summary>
class Plan
{
private:
    Formula** sequences; // Dynamic array to hold formula(s)
    int size; // Current size of the dynamic array
    int capacity; // Capacity of the dynamic array
    static const int DEFAULT = 0; // default value
    const int INDEX = 1;          // default index

public:
    /// <summary>
    /// Default Constructor
    /// Precondition: initialSize must be non-negative.
    /// Postcondition: A Plan object is created with initialSize number of Formula objects.
    /// </summary>
    Plan(Formula* initialSequences[] = nullptr, int initialSize = DEFAULT);

    /// <summary>
    /// Deep copy Constructor
    /// Precondition: The source Plan object must be valid.
    /// Postcondition: A new Plan object is created as a deep copy of the source.
    /// </summary>
    Plan(const Plan& source);

    /// <summary>
    /// Move Constructor
    /// Precondition: The source Plan object must be valid.
    /// Postcondition: The source Plan object is moved into the new Plan object.
    /// </summary>
    Plan(Plan&& source);

    /// <summary>
    /// Deep copy operator
    /// Precondition: The source Plan object must be valid.
    /// Postcondition: The current Plan object is a deep copy of the source.
    /// </summary>
    Plan& operator=(const Plan& source);

    /// <summary>
    /// Move operator
    /// Precondition: The source Plan object must be valid.
    /// Postcondition: The source Plan object is moved into the current Plan
    /// object. The source Plan object is empty.
    /// </summary>
    Plan& operator=(Plan&& source);

    /// <summary>
    /// Deconstructor
    /// Precondition: None.
    /// Postcondition: The Plan object is destroyed and its memory is freed.
    /// </summary>
    ~Plan();

    /// <summary>
    /// Add function
    /// Precondition: newFormula must be a valid Formula object.
    /// Postcondition: newFormula is added to the Plan object.
    /// </summary>
    void Add(Formula* newFormula);

    /// <summary>
    /// Remove function
    /// Precondition: The Plan object must contain at least one Formula object.
    /// Postcondition: The last Formula object in the Plan is removed.
    /// </summary>
    void Remove();

    /// <summary>
    /// Replace function
    /// Precondition: index must be a valid index in the Plan object,
    /// and newFormula must be a valid Formula object.
    /// Postcondition: The Formula object at the specified index in
    /// the Plan is replaced with newFormula.
    /// </summary>
    void Replace(int index, Formula* newFormula);

    /// <summary>
    /// To String function
    /// Precondition: None.
    /// Postcondition: A string representation of the Plan object is returned.
    /// </summary>
    std::string toString();
};

#endif // !PLAN_H