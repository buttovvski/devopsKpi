#include "FuncClass.h"
#include <cmath> // For pow and factorial
// FuncA calculates the sum of the first n terms of e^x
// Parameters:
//   - n: Number of terms to include in the sum
//   - x: Exponent for e^x

double FuncClass::FuncA(int n, double x) {
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        double term = std::pow(x, i) / std::tgamma(i + 1); // tgamma computes factorial as (n-1)!
        result += term;
    }
    return result;
}