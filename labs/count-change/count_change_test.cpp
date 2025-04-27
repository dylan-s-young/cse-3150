// count_change_test.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include <vector>

// Function declarations from our implementation files
int countChange(int amount, const std::vector<int> &coins);
int countChangeDP(int amount, const std::vector<int> &coins);

TEST_CASE("Count Change Basic Cases")
{
    std::vector<int> usCoins = {1, 5, 10, 25, 50};

    SUBCASE("Zero amount")
    {
        CHECK(countChange(0, usCoins) == 1);
        CHECK(countChangeDP(0, usCoins) == 1);
    }

    SUBCASE("Small amounts")
    {
        CHECK(countChange(1, usCoins) == 1);
        CHECK(countChangeDP(1, usCoins) == 1);

        CHECK(countChange(5, usCoins) == 2); // 5 cents: [5] or [1,1,1,1,1]
        CHECK(countChangeDP(5, usCoins) == 2);

        CHECK(countChange(10, usCoins) == 4); // 10 cents: [10], [5,5], [5,1,1,1,1,1], [1,1,1,1,1,1,1,1,1,1]
        CHECK(countChangeDP(10, usCoins) == 4);
    }

    SUBCASE("Medium amounts")
    {
        CHECK(countChange(25, usCoins) == 13);
        CHECK(countChangeDP(25, usCoins) == 13);

        CHECK(countChange(50, usCoins) == 50);
        CHECK(countChangeDP(50, usCoins) == 50);
    }

    SUBCASE("Larger amounts")
    {
        CHECK(countChange(100, usCoins) == 292);
        CHECK(countChangeDP(100, usCoins) == 292);
    }
}

TEST_CASE("Different coin sets")
{
    // 1, 2, 5 euro coins
    std::vector<int> euroCoins = {1, 2, 5};

    SUBCASE("Euro coins")
    {
        CHECK(countChange(5, euroCoins) == 4); // [5], [2,2,1], [2,1,1,1], [1,1,1,1,1]
        CHECK(countChangeDP(5, euroCoins) == 4);

        CHECK(countChange(10, euroCoins) == 10);
        CHECK(countChangeDP(10, euroCoins) == 10);
    }

    // Binary coins: 1, 2, 4, 8, 16
    std::vector<int> binaryCoins = {1, 2, 4, 8, 16};

    SUBCASE("Binary coins")
    {
        CHECK(countChange(20, binaryCoins) == 60);
        CHECK(countChangeDP(20, binaryCoins) == 60);
    }

    // Edge case: only one coin type
    std::vector<int> singleCoin = {5};

    SUBCASE("Single coin type")
    {
        CHECK(countChange(10, singleCoin) == 1); // Only one way: [5,5]
        CHECK(countChangeDP(10, singleCoin) == 1);

        CHECK(countChange(7, singleCoin) == 0); // Not possible
        CHECK(countChangeDP(7, singleCoin) == 0);
    }
}

TEST_CASE("Performance comparison")
{
    std::vector<int> usCoins = {1, 5, 10, 25, 50};

    // Test with a reasonably large amount
    int largeAmount = 200;

    // Both should produce the same result
    CHECK(countChange(largeAmount, usCoins) == countChangeDP(largeAmount, usCoins));
}