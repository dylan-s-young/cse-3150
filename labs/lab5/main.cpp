#include "CosDistance.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

struct VectorPair
{
    int index1;
    int index2;
    double distance;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string filename = argv[1];

    std::vector<std::vector<double>> vectors;
    try
    {
        vectors = readVectorsFromFile(filename);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading vectors: " << e.what() << std::endl;
        return 1;
    }

    int n = vectors.size();
    if (n < 2)
    {
        std::cerr << "Need at least two vectors to compute distances.\n";
        return 1;
    }

    // Compute pairwise cosine distances
    std::vector<VectorPair> pairs;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double dist = 0.0;
            try
            {
                dist = cosineDistance(vectors[i], vectors[j]);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error computing cosine distance between vector " << i
                          << " and vector " << j << ": " << e.what() << "\n";
                continue;
            }
            pairs.push_back({i, j, dist});
        }
    }

    // Sort pairs by ascending distance (closest pairs first)
    std::sort(pairs.begin(), pairs.end(), [](const VectorPair &a, const VectorPair &b)
              { return a.distance < b.distance; });

    // Output the sorted pairs with their cosine distances
    std::cout << "Pairwise Cosine Distances (Closest first):\n";
    for (const auto &pair : pairs)
    {
        std::cout << "Vector " << pair.index1 << " and Vector " << pair.index2
                  << " -> Cosine Distance: " << pair.distance << "\n";
    }

    return 0;
}