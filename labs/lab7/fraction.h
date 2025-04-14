#ifndef FRACTION_H
#define FRACTION_H

#include "bigint.h"
#include <utility>

// Define a Fraction as a pair: first = numerator, second = denominator.
using Fraction = std::pair<bigint, bigint>;

// Reduces a fraction (ensuring the denominator is positive).
Fraction reduceFraction(const Fraction &frac);

// Adds two fractions and returns the simplified result.
Fraction addFraction(const Fraction &f1, const Fraction &f2);

// Multiplies two fractions and returns the simplified result.
Fraction multiplyFraction(const Fraction &f1, const Fraction &f2);

#endif // FRACTION_H