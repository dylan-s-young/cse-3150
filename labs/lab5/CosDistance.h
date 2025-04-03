#ifndef COS_DISTANCE_H
#define COS_DISTANCE_H

#include <vector>
#include <string>

// Computes the cosine distance between two vectors.
// Cosine distance is defined as: 1 - cosine similarity.
double cosineDistance(const std::vector<double> &a, const std::vector<double> &b);

// Reads vectors from a file.
// Each line in the file represents a vector of doubles separated by whitespace.
std::vector<std::vector<double>> readVectorsFromFile(const std::string &filename);

#endif // COS_DISTANCE_H