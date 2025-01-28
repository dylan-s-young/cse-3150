#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <vector>
#include "./include/doctest.h"

// Function to check if the prefix sums never go below zero
bool non_neg_prefix_sum(const std::vector<int> &lst)
{
    int prefix_sum = 0;
    for (int num : lst)
    {
        prefix_sum += num;
        if (prefix_sum < 0)
        {
            return false;
        }
    }
    return true;
}

TEST_CASE("testing the non_neg_prefix_sum function")
{
    CHECK(non_neg_prefix_sum({1, 1, 1, 1, -1}) == true);
    CHECK(non_neg_prefix_sum({1, 2, 3, 5, -6}) == true);
    CHECK(non_neg_prefix_sum({1, -5, 2, 7, -1}) == false);
    CHECK(non_neg_prefix_sum({1, 1, 1, -10, -1}) == false);
    CHECK(non_neg_prefix_sum({1, 1, 1, 1, -2}) == true);
}

// Function to check if the prefix sums never go above zero
bool non_pos_prefix_sum(const std::vector<int> &lst)
{
    int prefix_sum = 0;
    for (int num : lst)
    {
        prefix_sum += num;
        if (prefix_sum > 0)
        {
            return false;
        }
    }
    return true;
}

TEST_CASE("Testing the non_pos_prefix_sum function")
{
    CHECK(non_pos_prefix_sum({-1, -2, -3}) == true);
    CHECK(non_pos_prefix_sum({-1, -5, -3}) == true);
    CHECK(non_pos_prefix_sum({-1, 10, -10}) == false);
    CHECK(non_pos_prefix_sum({-1, -1, -1, 4, -1}) == false);
    CHECK(non_pos_prefix_sum({-1, -9, -3}) == true);
}