#include <iostream>
#include <cmath>
#include "../solver.h"

const double pi = 3.141592654;

Function funcA ([](double x) { return 1 / x - tan (x); });
Function funcB ([](double x) { return 1 / x - pow (2, x); });
Function funcC ([](double x) { return pow (2, -1 * x) + exp (x) + 2 * cos (x) - 6; });
Function funcD ([](double x) { return (x * x * x + 4 * x * x + 3 * x + 5) / (2 * x * x * x - 9 * x * x + 18 * x - 2); });

BisectionSolver bisection;

int main () {
    std :: cout << "Bisection Method" << std :: endl;
    std :: cout << "Function A: " << bisection.solve (funcA, 0, pi / 2) << std :: endl;
    std :: cout << "Function B: " << bisection.solve (funcB, 0, 1) << std :: endl;
    std :: cout << "Function C: " << bisection.solve (funcC, 1, 3) << std :: endl;
    std :: cout << "Function D: " << bisection.solve (funcD, 0, 4) << std :: endl;
    return 0;
}