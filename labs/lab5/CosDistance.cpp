#include "CosDistance.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

double cosineDistance(const std::vector<double> &a, const std::vector<double> &b)
{
    if (a.size() != b.size())
    {
        throw std::invalid_argument("Vectors must be of the same dimension.");
    }
    double dot = 0.0;
    double normA = 0.0;
    double normB = 0.0;
    for (size_t i = 0; i < a.size(); i++)
    {
        dot += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }
    if (normA == 0 || normB == 0)
    {
        throw std::runtime_error("One of the vectors has zero magnitude.");
    }
    double cosineSimilarity = dot / (std::sqrt(normA) * std::sqrt(normB));
    // Cosine distance is defined as 1 - cosine similarity
    return 1.0 - cosineSimilarity;
}

std::vector<std::vector<double>> readVectorsFromFile(const std::string &filename)
{
    std::vector<std::vector<double>> vectors;
    std::ifstream infile(filename);
    if (!infile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::vector<double> vec;
        double value;
        while (iss >> value)
        {
            vec.push_back(value);
        }
        if (!vec.empty())
        {
            vectors.push_back(vec);
        }
    }
    // Ensure all vectors have the same dimension
    if (!vectors.empty())
    {
        size_t dim = vectors[0].size();
        for (const auto &vec : vectors)
        {
            if (vec.size() != dim)
            {
                throw std::runtime_error("Not all vectors have the same dimension.");
            }
        }
    }
    return vectors;
}