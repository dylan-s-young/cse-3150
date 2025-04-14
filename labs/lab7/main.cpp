#include <iostream>
#include <chrono>
#include "bigint.h"
#include "fraction.h"

using namespace std;
using namespace std::chrono;

//
// Test fraction operations: addition and multiplication
//
void testFractionOperations()
{
    Fraction f1 = std::make_pair(bigint("1"), bigint("2"));
    Fraction f2 = std::make_pair(bigint("3"), bigint("4"));

    // Fraction addition: (1/2 + 3/4) should reduce to 5/4.
    Fraction sum = addFraction(f1, f2);
    cout << "Fraction addition (1/2 + 3/4): "
         << sum.first << " / " << sum.second << endl;

    // Fraction multiplication: (1/2 * 3/4) should reduce to 3/8.
    Fraction product = multiplyFraction(f1, f2);
    cout << "Fraction multiplication (1/2 * 3/4): "
         << product.first << " / " << product.second << endl;
}

//
// Timing tests using C++11 chrono library.
// We use a higher iteration count and volatile accumulators for int and long to ensure measurable times.
//
void timeTest()
{
    // Use a large iteration count for int and long tests.
    const long long iterations = 100000000; // 100 million iterations

    // Use volatile accumulators to prevent loop optimization.
    volatile int dummy_int = 0;
    int a = 1, b = 2;
    auto start = high_resolution_clock::now();
    for (long long i = 0; i < iterations; i++)
    {
        dummy_int += a + b;
    }
    auto end = high_resolution_clock::now();
    auto duration_int = duration_cast<microseconds>(end - start).count();

    volatile long int dummy_long = 0;
    long int la = 1L, lb = 2L;
    start = high_resolution_clock::now();
    for (long long i = 0; i < iterations; i++)
    {
        dummy_long += la + lb;
    }
    end = high_resolution_clock::now();
    auto duration_long = duration_cast<microseconds>(end - start).count();

    // Use fewer iterations for bigint because it's much slower.
    const int bigintIterations = 1000000;
    bigint ba("1"), bb("2"), bc("0");
    start = high_resolution_clock::now();
    for (int i = 0; i < bigintIterations; i++)
    {
        bc = ba + bb;
    }
    end = high_resolution_clock::now();
    auto duration_bigint = duration_cast<microseconds>(end - start).count();

    cout << "\nTiming over:" << endl;
    cout << "  " << iterations << " iterations for int addition: " << duration_int << " microseconds." << endl;
    cout << "  " << iterations << " iterations for long int addition: " << duration_long << " microseconds." << endl;
    cout << "  " << bigintIterations << " iterations for bigint addition: " << duration_bigint << " microseconds." << endl;

    // Demonstrate potential overflow with int multiplication and safe bigint multiplication.
    int largeInt1 = 1000000, largeInt2 = 1000000;
    int intProduct = largeInt1 * largeInt2;
    cout << "\nint multiplication (1000000 * 1000000): "
         << intProduct << " (may overflow)" << endl;

    bigint big1("1000000"), big2("1000000");
    bigint bigProduct = big1 * big2;
    cout << "bigint multiplication (1000000 * 1000000): "
         << bigProduct << endl;
}

int main()
{
    cout << "Lab: BigInts Tests\n";

    testFractionOperations();
    timeTest();

    return 0;
}