#ifndef PLAN_H
#define PLAN_H

#include "formula.h"

class Plan
{
private:
    Formula** sequences; // Dynamic array to hold formula(s)
    int size; // Current size of the dynamic array
    int capacity; // Capacity of the dynamic array

public:
    // Default Constructor
    Plan(Formula* initialSequences[] = nullptr, int initialSize = 0);

    // Deep copy Constructor
    Plan(const Plan& source);

    // Move Constructor
    Plan(Plan&& source);

    // Deep copy operator
    Plan& operator=(const Plan& source);

    // Move operator
    Plan& operator=(Plan&& source);

    // Deconstructor
    ~Plan();

    // Add function
    void Add(Formula* newFormula);

    // Remove function
    void Remove();

    // Replace function
    void Replace(int index, Formula* newFormula);

    // To String function
    std::string toString();
};

#endif // !PLAN_H
