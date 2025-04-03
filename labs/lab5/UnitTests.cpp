#include "CosDistance.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

void testCosineDistanceIdenticalVectors()
{
    std::vector<double> a = {1.0, 2.0, 3.0};
    std::vector<double> b = {1.0, 2.0, 3.0};
    double dist = cosineDistance(a, b);
    // For identical vectors, cosine similarity is 1 so distance should be 0.
    assert(std::abs(dist - 0.0) < 1e-6);
}

void testCosineDistanceOppositeVectors()
{
    std::vector<double> a = {1.0, 0.0};
    std::vector<double> b = {-1.0, 0.0};
    double dist = cosineDistance(a, b);
    // For opposite vectors, cosine similarity is -1 so distance should be 2.
    assert(std::abs(dist - 2.0) < 1e-6);
}

void testCosineDistanceOrthogonalVectors()
{
    std::vector<double> a = {1.0, 0.0};
    std::vector<double> b = {0.0, 1.0};
    double dist = cosineDistance(a, b);
    // For orthogonal vectors, cosine similarity is 0 so distance should be 1.
    assert(std::abs(dist - 1.0) < 1e-6);
}

int main()
{
    try
    {
        testCosineDistanceIdenticalVectors();
        testCosineDistanceOppositeVectors();
        testCosineDistanceOrthogonalVectors();
        std::cout << "All tests passed successfully.\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "A test failed with exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}