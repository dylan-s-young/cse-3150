#include "fraction.h"
#include <stdexcept>

//
// Updated reduceFraction function.
// - Uses local variables for numerator and denominator.
// - Checks for denominator zero using the local copy.
// - Uses the big_abs macro rather than accessing private members.
//
Fraction reduceFraction(const Fraction &frac)
{
    // Create local copies (non-const) of the numerator and denominator.
    bigint num = frac.first;
    bigint den = frac.second;

    // Check if the denominator is zero.
    if (den == bigint("0"))
        throw std::runtime_error("Denominator is zero in fraction reduction.");

    // Make denominator positive.
    if (den < bigint("0"))
    {
        num = num * bigint("-1");
        den = den * bigint("-1");
    }

    // Compute the gcd using the absolute value of the numerator.
    // Use the big_abs macro (which expands to bigint::_big_abs) instead of accessing num.str.
    bigint absNum = big_abs(num);
    bigint gcd = bigint::_big_gcd(absNum, den);

    // Divide both numerator and denominator by gcd.
    return std::make_pair(num / gcd, den / gcd);
}

//
// addFraction: computes (a/b) + (c/d) = (a*d + c*b) / (b*d)
//
Fraction addFraction(const Fraction &f1, const Fraction &f2)
{
    // Make local copies for easy use.
    bigint a = f1.first;
    bigint b = f1.second;
    bigint c = f2.first;
    bigint d = f2.second;

    // Compute numerator and denominator.
    bigint num = a * d + c * b;
    bigint den = b * d;
    return reduceFraction(std::make_pair(num, den));
}

//
// multiplyFraction: computes (a/b) * (c/d) = (a*c) / (b*d)
//
Fraction multiplyFraction(const Fraction &f1, const Fraction &f2)
{
    // Copy the fraction components locally.
    bigint a = f1.first;
    bigint b = f1.second;
    bigint c = f2.first;
    bigint d = f2.second;

    bigint num = a * c;
    bigint den = b * d;
    return reduceFraction(std::make_pair(num, den));
}