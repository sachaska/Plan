#include "plan.h"
#include <stdexcept>
#include <sstream>

// Default Constructor
Plan::Plan(Formula* initialSequences[], int initialSize)
        : sequences(nullptr), size(0), capacity(0)
{
    if (initialSequences != nullptr && initialSize > 0)
    {
        sequences = new Formula*[initialSize];
        for (int i = 0; i < initialSize; ++i)
        {
            sequences[i] = new Formula(*initialSequences[i]);
        }
        size = capacity = initialSize;
    }
}

// Deep copy Constructor
Plan::Plan(const Plan& source)
        : sequences(nullptr), size(0), capacity(0)
{
    if (source.size > 0)
    {
        sequences = new Formula*[source.size];
        for (int i = 0; i < source.size; ++i)
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
    source.size = source.capacity = 0;
}

// Deep copy operator
Plan& Plan::operator=(const Plan& source)
{
    if (this != &source)
    {
        // Release existing resources
        for (int i = 0; i < size; ++i)
        {
            delete sequences[i];
        }
        delete[] sequences;

        // Copy from the source
        if (source.size > 0)
        {
            sequences = new Formula*[source.size];
            for (int i = 0; i < source.size; ++i)
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
        for (int i = 0; i < size; ++i)
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
        source.size = source.capacity = 0;
    }
    return *this;
}

// Deconstructor
Plan::~Plan()
{
    for (int i = 0; i < size; ++i)
    {
        if (sequences[i] != nullptr)
            delete sequences[i];
    }
    delete[] sequences;
}

// Add function
void Plan::Add(Formula* newFormula)
{
    if (size == capacity)
    {
        // Resize the dynamic array (double the capacity)
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Formula** newArray = new Formula*[newCapacity];

        // Copy existing elements
        for (int i = 0; i < size; ++i)
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
    if (size > 0)
    {
        // Delete the last formula
        delete sequences[size - 1];
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
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Replace failed. Index out of range.");
    }

    // Delete the existing formula at the specified index
    delete sequences[index];
    sequences[index] = nullptr;

    // Store the pointer to the new formula at the specified index
    sequences[index] = newFormula;
}

std::string Plan::toString() {
    // each formula to string
    std::ostringstream os;
    for (int i = 0; i < size; ++i)
    {
        os << sequences[i]->toString() << "\n";
    }
    return os.str();
}