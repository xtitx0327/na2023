#include <iostream>
#include <cmath>
#include "../solver.h"

const double pi = 3.14159265;

SecantSolver secant;

Function funcA ([](double x) { return sin (x / 2) - 1; });
Function funcB ([](double x) { return exp (x) - tan (x); });
Function funcC ([](double x) { return x * x * x - 12 * x * x + 3 * x + 1; });

int main () {
    std :: cout << "Function A (with 0, pi / 2): " << secant.solve (funcA, 0, pi / 2) << std :: endl;
    std :: cout << "Function B (with 1, 1.4): " << secant.solve (funcB, 1, 1.4) << std :: endl;
    std :: cout << "Function C (with 0, -0.5): " << secant.solve (funcC, 0, -0.5) << std :: endl;
    return 0;
}