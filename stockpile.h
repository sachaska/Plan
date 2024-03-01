#ifndef PA2_STOCKPILE_H
#define PA2_STOCKPILE_H

/// Author: Ai Sun
///   Date: 2023, Feb 29
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */


#include<map>

/// <summary>
/// Class representing a stockpile of resources.
/// Class Invariant: The quantities of resources must always be non-negative.
/// </summary>
class stockpile {
    std::map<std::string, int> supplies;
                                // Holds set of resources with their quantities.

    const int DEFAULT = 0;      // constant value default

public:
    /// <summary>
    /// Default Constructor
    /// Precondition: None.
    /// Postcondition: A stockpile object is created with no resources.
    /// </summary>
    stockpile();

    /// <summary>
    /// Constructor
    /// Precondition: input must not be empty, quantities must be non-negative.
    /// Postcondition: A stockpile object is created with given resources.
    /// </summary>
    stockpile(std::map<std::string, int> input);

    /// <summary>
    /// Query function
    /// Precondition: None.
    /// Postcondition: A string representation of the stockpile object is returned.
    /// </summary>
    std::string query();

    /// <summary>
    /// Get Supplies function
    /// Precondition: None.
    /// Postcondition: A map of the stockpile's resources is returned.
    /// </summary>
    std::map<std::string, int> getSupplies();

    /// <summary>
    /// Is Empty function
    /// Precondition: None.
    /// Postcondition: Returns true if the stockpile is empty, false otherwise.
    /// </summary>
    bool isEmpty();

    /// <summary>
    /// Add function
    /// Precondition: name must not be empty, quantity must be non-negative.
    /// Postcondition: The specified resource is added to the stockpile
    /// with the given quantity.
    /// </summary>
    void add(const std::string& name, int quantity);

    /// <summary>
    /// Remove function
    /// Precondition: name must not be empty.
    /// Postcondition: The specified resource is removed from the stockpile.
    /// </summary>
    void remove(const std::string& name);

    /// <summary>
    /// Increase function
    /// Precondition: name must not be empty, quantity must be non-negative.
    /// Postcondition: The quantity of the specified resource in the
    /// stockpile is increased by the given quantity.
    /// </summary>
    void increase(const std::string& name, int quantity);

    /// <summary>
    /// Decrease function
    /// Precondition: name must not be empty, quantity must be non-negative.
    /// Postcondition: The quantity of the specified resource in the stockpile
    /// is decreased by the given quantity.
    /// </summary>
    void decrease(const std::string& name, int quantity);

    /// <summary>
    /// Destructor
    /// Precondition: None.
    /// Postcondition: The stockpile object is destroyed and its memory is freed.
    /// </summary>
    ~stockpile();
};

#endif //PA2_STOCKPILE_H