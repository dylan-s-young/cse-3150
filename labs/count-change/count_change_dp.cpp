#include <iostream>
#include <vector>

// Count the number of ways to make change using dynamic programming (bottom-up approach)
int countChangeDP(int amount, const std::vector<int> &coins)
{
    // Create a table to store results of subproblems
    std::vector<int> dp(amount + 1, 0);

    // Base case: there is 1 way to make change for amount 0 (using no coins)
    dp[0] = 1;

    // Fill the dp table in bottom-up manner
    for (int coin : coins)
    {
        for (int i = coin; i <= amount; i++)
        {
            dp[i] += dp[i - coin];
        }
    }

    return dp[amount];
}

#ifndef TESTING
// REMOVE the main function block ENTIRELY
#endif