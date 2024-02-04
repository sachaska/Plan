#include "plan.h"
#include <stdexcept>
#include <sstream>

/// Author: Ai Sun
///   Date: 2023, Feb 2
///   Platform: CLion (Mac)

/// Revision History:
/*      - 2024, Feb 1 Ai Sun - Initial creation of the class.
 */

/*
 * This is the implementation of plan.h. The Plan class represents a plan that
 * contains a dynamic array of Formula objects.
 * Each Formula object represents a formula that can be used to convert certain
 * input materials into certain output materials.
 * The Plan class provides methods to add a new Formula to the plan, remove the
 * last Formula from the plan, and replace a
 * Formula at a specific index in the plan. It also provides methods to create a
 * deep copy of a Plan object, move a Plan object,
 * and convert a Plan object to a string.
 *
 * Implementation Invariant:
 * The Plan class maintains a dynamic array of Formula objects, represented as a
 * double pointer to Formula. The size of the
 * dynamic array is always non-negative, and the capacity of the dynamic array
 * is always greater than or equal to the size.
 * The Plan class ensures that the dynamic array is properly resized when a new
 * Formula is added and there is no more space
 * left in the array. It also ensures that the dynamic array and all Formula
 * objects it contains are properly deleted when a
 * Plan object is destroyed.
 *
 * Error Processing:
 * The Plan class checks for errors in its methods and throws exceptions when
 * errors occur. For example, it throws an
 * std::invalid_argument exception if the initial size of the dynamic array is
 * negative, an std::underflow_error exception
 * if the Remove method is called when the dynamic array is empty, and an
 * std::out_of_range exception if the Replace method
 * is called with an invalid index.
 *
 * Assumptions:
 * The Plan class assumes that all Formula objects passed to its methods
 * are valid. It does not check the validity of Formula
 * objects. It also assumes that the index passed to the Replace method
 * is a valid index in the dynamic array. It does not
 * check the validity of the index.
 */

// Default Constructor
Plan::Plan(Formula* initialSequences[], int initialSize)
        : sequences(nullptr), size(DEFAULT), capacity(DEFAULT)
{
    if (initialSize < DEFAULT)
    {
        throw std::invalid_argument
        ("Initial size must be a non-zero number.");
    }

    if (initialSequences != nullptr)
    {
        sequences = new Formula*[initialSize];
        for (int i = DEFAULT; i < initialSize; ++i)
        {
            sequences[i] = new Formula(*initialSequences[i]);
        }
        size = capacity = initialSize;
    }
}

// Deep copy Constructor
Plan::Plan(const Plan& source)
        : sequences(nullptr), size(DEFAULT), capacity(DEFAULT)
{
    if (source.size > DEFAULT)
    {
        sequences = new Formula*[source.size];
        for (int i = DEFAULT; i < source.size; ++i)
        {
            sequences[i] = new Formula(*source.sequences[i]);
        }
        size = capacity = source.size;
    }
}

// Move Constructor
Plan::Plan(Plan&& source)
        : sequences(source.sequences), size(source.size),
        capacity(source.capacity)
{
    // Nullify the source object to prevent double deletion
    source.sequences = nullptr;
    source.size = source.capacity = DEFAULT;
}

// Deep copy operator
Plan& Plan::operator=(const Plan& source)
{
    if (this != &source)
    {
        // Release existing resources
        for (int i = DEFAULT; i < size; ++i)
        {
            delete sequences[i];
        }
        delete[] sequences;

        // Copy from the source
        if (source.size > DEFAULT)
        {
            sequences = new Formula*[source.size];
            for (int i = DEFAULT; i < source.size; ++i)
            {
                sequences[i] = new Formula(*source.sequences[i]);
            }
            size = capacity = source.size;
        }
    }
    return *this;
}

// Move operator
Plan& Plan::operator=(Plan&& source)
{
    if (this != &source)
    {
        // Release existing resources
        for (int i = DEFAULT; i < size; ++i)
        {
            delete sequences[i];
        }

        delete[] sequences;

        // Move from the source
        sequences = source.sequences;
        size = source.size;
        capacity = source.capacity;

        // Nullify the source object to prevent double deletion
        source.sequences = nullptr;
        source.size = source.capacity = DEFAULT;
    }
    return *this;
}

// Deconstructor
Plan::~Plan()
{
    for (int i = DEFAULT; i < size; ++i)
    {
        if (sequences[i] != nullptr)
            delete sequences[i];
    }
    delete[] sequences;
}

// Add function
void Plan::Add(Formula* newFormula)
{
    const int INITIAL = 1;
    const int DOUBLE = 2;

    if (size == capacity)
    {
        // Resize the dynamic array (double the capacity)
        int newCapacity = (capacity == DEFAULT) ? INITIAL : capacity * DOUBLE;
        Formula** newArray = new Formula*[newCapacity];

        // Copy existing elements
        for (int i = DEFAULT; i < size; ++i)
        {
            newArray[i] = sequences[i];
        }

        // Add the new formula
        newArray[size] = new Formula(*newFormula);

        // Delete the old array and update the pointers
        delete[] sequences;
        sequences = newArray;
        capacity = newCapacity;
    }
    else
    {
        // There is space in the array, simply add the new formula
        sequences[size] = new Formula(*newFormula);
    }

    // Increment the size
    ++size;
}


// Remove function
void Plan::Remove()
{

    if (size > DEFAULT)
    {
        // Delete the last formula
        delete sequences[size - INDEX];
        --size;
    }
    else
    {
        throw std::underflow_error("Remove failed. No formula to remove.");
    }
}

// Replace function
void Plan::Replace(int index, Formula* newFormula)
{
    if (index < DEFAULT || index >= size)
    {
        throw std::out_of_range("Replace failed. Index out of range.");
    }

    // Delete the existing formula at the specified index
     delete sequences[index];
     sequences[index] = nullptr;

    // Store the pointer to the new formula at the specified index
    sequences[index] = new Formula(*newFormula);
}

// To string function
std::string Plan::toString() {
    // each formula to string
    std::ostringstream os;

    for (int i = DEFAULT; i < size; ++i)
    {
        os << "(" << i + INDEX << ") " << sequences[i]->toString() << "\n";
    }

    return os.str();
}