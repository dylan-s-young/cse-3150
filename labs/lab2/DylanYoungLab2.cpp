#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <vector>
#include <cstdlib> // For std::rand, std::srand
#include <ctime>   // For std::time
#include "./include/doctest.h"

// Given a list of 2𝑛 integers, fill the first 𝑛 elements with 1 and the next 𝑛 elements with -1.
std::vector<int> fillList(int n)
{
    std::vector<int> result(2 * n);
    std::fill(result.begin(), result.begin() + n, 1);
    std::fill(result.begin() + n, result.end(), -1);
    return result;
}

TEST_CASE("Testing fillList Function")
{
    SUBCASE("Check if the list has correct size")
    {
        int n = 5;
        std::vector<int> result = fillList(n);
        CHECK(result.size() == 2 * n);
    }

    SUBCASE("Check if first half contains only 1s")
    {
        int n = 5;
        std::vector<int> result = fillList(n);
        for (int i = 0; i < n; ++i)
        {
            CHECK(result[i] == 1);
        }
    }

    SUBCASE("Check if second half contains only -1s")
    {
        int n = 5;
        std::vector<int> result = fillList(n);
        for (int i = n; i < 2 * n; ++i)
        {
            CHECK(result[i] == -1);
        }
    }

    SUBCASE("Check for different values of n")
    {
        for (int n : {1, 10, 50})
        {
            std::vector<int> result = fillList(n);
            CHECK(result.size() == 2 * n);
            CHECK(std::all_of(result.begin(), result.begin() + n, [](int x)
                              { return x == 1; }));
            CHECK(std::all_of(result.begin() + n, result.end(), [](int x)
                              { return x == -1; }));
        }
    }
}

// Fisher-Yates shuffle function
void fisherYatesShuffle(std::vector<int> &arr)
{
    for (size_t i = arr.size() - 1; i > 0; --i)
    {
        int j = std::rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

TEST_CASE("Testing fisherYatesShuffle Function")
{
    SUBCASE("Check if shuffle preserves all elements")
    {
        int n = 5;
        std::vector<int> original = fillList(n);
        std::vector<int> shuffled = original;

        fisherYatesShuffle(shuffled);

        // Check if both vectors contain the same elements
        CHECK(std::is_permutation(original.begin(), original.end(), shuffled.begin()));
    }

    SUBCASE("Check if shuffle changes order in most cases")
    {
        int n = 5;
        std::vector<int> original = fillList(n);
        std::vector<int> shuffled = original;

        fisherYatesShuffle(shuffled);

        // Check if at least one element is in a different position (probabilistic test)
        bool changed = false;
        for (size_t i = 0; i < original.size(); ++i)
        {
            if (original[i] != shuffled[i])
            {
                changed = true;
                break;
            }
        }
        CHECK(changed);
    }
}

// Function to check if the prefix sums never go below zero
// These functions were from previous lab, they work.
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

// Function to check if the prefix sums never go above zero
// These functions were from previous lab, they work.
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

void compute_proportion(int n, int iterations)
{
    int valid_count = 0;
    int total_count = 0;

    for (int i = 0; i < iterations; i++)
    {
        std::vector<int> list = fillList(n);
        fisherYatesShuffle(list);

        if (non_neg_prefix_sum(list) || non_pos_prefix_sum(list))
        {
            valid_count++;
        }
        total_count++;
    }

    double proportion = static_cast<double>(valid_count) / total_count;
    std::cout << "Total Sequences Generated: " << total_count << std::endl;
    std::cout << "Valid Well-Balanced Sequences: " << valid_count << std::endl;
    std::cout << "Proportion of Well-Balanced Sequences: " << proportion << std::endl;
}

int main()
{
    std::srand(std::time(0));
    int n = 5;
    int iterations = 1000000;

    compute_proportion(n, iterations);

    return 0;
}