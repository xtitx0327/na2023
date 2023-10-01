#include <iostream>
#include <cmath>
#include "../solver.h"

const double pi = 3.14159265;

Function func([](double x) { return 10 * (0.5 * pi - asin (x) - x * sqrt (1 - x * x)) - 12.4; });
Function derFunc([](double x) { return 10 * (- 1 / sqrt(1 - x * x) -  1 / pow (1 - x * x, 1.5)); });

BisectionSolver bisection;
NewtonSolver newton;
SecantSolver secant;

int main () {
    std :: cout << "Depth (ft) solved by bisection method: " << 1 - bisection.solve (func, 0, 1) << std :: endl;
    std :: cout << "Depth (ft) solved by Newton's method: " << 1 - newton.solve (func, derFunc, 0.8) << std :: endl;
    std :: cout << "Depth (ft) solved by secant method: " << 1 - secant.solve (func, 0, 1) << std :: endl;
    return 0;
}