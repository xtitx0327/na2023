#include <iostream>
#include <cmath>
#include "../solver.h"

NewtonSolver newton;

Function func ([](double x) { return x - tan (x); });
Function derFunc ([](double x) { return 1 - 1 / (cos (x) * cos (x)); });

int main() {
    std :: cout << "Root near 4.5: " << newton.solve (func, derFunc, 4.5) << std :: endl;
    std :: cout << "Root near 7.7: " << newton.solve (func, derFunc, 7.7) << std :: endl;
    return 0;
}