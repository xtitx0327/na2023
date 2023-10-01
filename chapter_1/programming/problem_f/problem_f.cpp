#include <iostream>
#include <cmath>
#include "../solver.h"

const double pi = 3.1415926536536;
const double l = 89, h = 49, beta1 = 11.5 / 180 * pi;
double A, B, C, D = 55, E;

void updateValues () {
    A = l * sin (beta1);
    B = l * cos (beta1);
    C = (h + 0.5 * D) * sin (beta1) - 0.5 * D * tan (beta1);
    E = (h + 0.5 * D) * cos (beta1) - 0.5 * D;
}

// Let x = sin(alpha)
Function func ([](double x){ return A * x * sqrt(1 - x * x) + B * x * x - C * sqrt(1 - x * x) - E * x; });
Function derFunc ([](double x){ return A * (1 - 2 * x * x) / sqrt (1 - x * x) + 2 * B * x + C * x / sqrt (1 - x * x) - E; });

NewtonSolver newton;
SecantSolver secant;

int main () {
    updateValues ();
    std :: cout << "Question (a): " << std :: endl;
    std :: cout << "The solution of alpha is: " << asin(newton.solve (func, derFunc, 0.5)) / pi * 180 << " (degree)." << std :: endl << std :: endl;

    D = 30;
    updateValues ();
    std :: cout << "Question (b): " << std :: endl;
    std :: cout << "The solution of alpha is: " << asin(newton.solve (func, derFunc, 0.5)) / pi * 180 << " (degree)." << std :: endl << std :: endl;

    std :: cout << "Question (c): " << std :: endl;
    std :: cout << "The solution of alpha is: " << asin(secant.solve (func, 0, 0.1)) / pi * 180 << " (degree)." << std :: endl << std :: endl;

    return 0;
}