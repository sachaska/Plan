#ifndef EXECUTABLEPLAN_H
#define EXECUTABLEPLAN_H

/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */

#include "plan.h"
#include "Stockpile.h"

/// <summary>
/// Class representing an executable plan.
/// Class Invariant: Inherits from Plan class, maintains a current index to
/// track progress of the plan.
/// </summary>
class ExecutablePlan : public Plan {
private:
    int current; // Current index to track progress

public:
    /// <summary>
    /// Constructor
    /// Precondition: initialSequences must be a valid array of Formula pointers,
    /// initialSize must be non-negative.
    /// Postcondition: An ExecutablePlan object is created with given initial
    /// sequences and size.
    /// </summary>
    ExecutablePlan(Formula* initialSequences[] = nullptr, int initialSize = DEFAULT);

    /// <summary>
    /// Apply function
    /// Precondition: None.
    /// Postcondition: A string representation of the production rate and
    /// simulation result is returned.
    /// </summary>
    std::string Apply() override;

    std::shared_ptr<Stockpile> Apply(const std::shared_ptr<Stockpile>&);

    /// <summary>
    /// Query function
    /// Precondition: None.
    /// Postcondition: A string representation of the production rate and
    /// simulation result is returned.
    /// </summary>
    std::string Query() override;

    /// <summary>
    /// Replace function
    /// Precondition: index must be a valid index in the plan, newFormula
    /// must be a valid Formula object.
    /// Postcondition: The Formula at the specified index in the plan is
    /// replaced with newFormula.
    /// </summary>
    void Replace(int index, Formula* newFormula) override;

    /// <summary>
    /// Remove function
    /// Precondition: The plan must contain at least one Formula.
    /// Postcondition: The last Formula in the plan is removed.
    /// </summary>
    void Remove() override;

    /// <summary>
    /// Clone function
    /// Precondition: None.
    /// Postcondition: A pointer to a new ExecutablePlan object, which is a
    /// deep copy of the current ExecutablePlan object, is returned.
    /// </summary>
    Plan* Clone() override;

    /// <summary>
    /// Equality operator
    /// Precondition: None.
    /// Postcondition: Returns true if the two ExecutablePlan objects are equal,
    /// false otherwise.
    /// </summary>
    bool operator==(const ExecutablePlan& other) const;

    /// <summary>
    /// Inequality operator
    /// Precondition: None.
    /// Postcondition: Returns true if the two ExecutablePlan objects are not
    /// equal, false otherwise.
    /// </summary>
    bool operator!=(const ExecutablePlan& other) const;
};

#endif // EXECUTABLEPLAN_H