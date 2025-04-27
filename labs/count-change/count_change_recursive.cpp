#include <iostream>
#include <vector>

// Count the number of ways to make change for amount using the first n coin denominations
int countChange(int amount, const std::vector<int> &coins, int n)
{
    // Base cases
    if (amount == 0)
        return 1; // Found a valid way to make change
    if (amount < 0 || n == 0)
        return 0; // Invalid path or no coins left

    // Recursive cases:
    // 1. Count ways excluding the current coin
    // 2. Count ways including the current coin
    return countChange(amount, coins, n - 1) +
           countChange(amount - coins[n - 1], coins, n);
}

// Wrapper function with simpler interface
int countChange(int amount, const std::vector<int> &coins)
{
    return countChange(amount, coins, coins.size());
}

#ifndef TESTING
// REMOVE the main function block ENTIRELY
#endif