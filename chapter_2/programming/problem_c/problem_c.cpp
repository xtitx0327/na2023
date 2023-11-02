#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "../interpolation.h"

const double PI = 3.14159265358979323846;

// Function to be interpolated
double f(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

// Zeros of Chebyshev polynomials
double chebyshevZero(int n, int i) {
    return cos((2 * i - 1) * PI / (2 * n));
}


int main() {
    // Values of n
    std::vector<int> n_values = {5, 10, 15, 20};

    for (int n : n_values) {
        std::vector<double> x(n);
        std::vector<double> y(n);

        // Get zeros of Chebyshev polynomials
        for (int i = 1; i <= n; i++) {
            x[i - 1] = chebyshevZero(n, i);
            y[i - 1] = f(x[i - 1]);
        }

        std::cout << "n = " << n << ":\n";
        std::cout << std::fixed << std::setprecision(5);

        for (double point = -1.0; point <= 1.0; point += 0.05) {
            std::cout << "x = " << point << ", f(x) = " << f(point) << ", P(x) = " << newtonInterpolation(x, y, point) << '\n';
        }
        std::cout << "\n";
    }

    return 0;
}
