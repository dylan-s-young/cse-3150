#include <iostream>
#include <cassert>
#include "fraction.h"

// Test addFraction function.
void testAddFractions()
{
    {
        // Test: 1/2 + 1/2 = 1/1
        Fraction f1 = std::make_pair(bigint("1"), bigint("2"));
        Fraction f2 = std::make_pair(bigint("1"), bigint("2"));
        Fraction result = addFraction(f1, f2);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("1"));
    }

    {
        // Test: 1/2 + 1/3 = 5/6
        Fraction f1 = std::make_pair(bigint("1"), bigint("2"));
        Fraction f2 = std::make_pair(bigint("1"), bigint("3"));
        Fraction result = addFraction(f1, f2);
        assert(result.first == bigint("5"));
        assert(result.second == bigint("6"));
    }

    {
        // Test: 2/3 + (-1)/3 = 1/3
        Fraction f1 = std::make_pair(bigint("2"), bigint("3"));
        Fraction f2 = std::make_pair(bigint("-1"), bigint("3"));
        Fraction result = addFraction(f1, f2);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("3"));
    }
}

// Test multiplyFraction function.
void testMultiplyFractions()
{
    {
        // Test: 1/2 * 1/3 = 1/6
        Fraction f1 = std::make_pair(bigint("1"), bigint("2"));
        Fraction f2 = std::make_pair(bigint("1"), bigint("3"));
        Fraction result = multiplyFraction(f1, f2);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("6"));
    }

    {
        // Test: (-1)/2 * 1/3 = (-1)/6
        Fraction f1 = std::make_pair(bigint("-1"), bigint("2"));
        Fraction f2 = std::make_pair(bigint("1"), bigint("3"));
        Fraction result = multiplyFraction(f1, f2);
        assert(result.first == bigint("-1"));
        assert(result.second == bigint("6"));
    }

    {
        // Test: (-1)/2 * (-2)/3 = 1/3
        Fraction f1 = std::make_pair(bigint("-1"), bigint("2"));
        Fraction f2 = std::make_pair(bigint("-2"), bigint("3"));
        Fraction result = multiplyFraction(f1, f2);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("3"));
    }
}

// Test reduceFraction function.
void testReduceFraction()
{
    {
        // Test: 2/4 should reduce to 1/2.
        Fraction f = std::make_pair(bigint("2"), bigint("4"));
        Fraction result = reduceFraction(f);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("2"));
    }

    {
        // Test: -2/4 should reduce to -1/2.
        Fraction f = std::make_pair(bigint("-2"), bigint("4"));
        Fraction result = reduceFraction(f);
        assert(result.first == bigint("-1"));
        assert(result.second == bigint("2"));
    }

    {
        // Test: -2/-4 should reduce to 1/2.
        Fraction f = std::make_pair(bigint("-2"), bigint("-4"));
        Fraction result = reduceFraction(f);
        assert(result.first == bigint("1"));
        assert(result.second == bigint("2"));
    }

    {
        // Test: 3/ -9 should reduce to -1/3.
        Fraction f = std::make_pair(bigint("3"), bigint("-9"));
        Fraction result = reduceFraction(f);
        assert(result.first == bigint("-1"));
        assert(result.second == bigint("3"));
    }
}

int main()
{
    testAddFractions();
    testMultiplyFractions();
    testReduceFraction();

    std::cout << "All fraction tests passed." << std::endl;
    return 0;
}