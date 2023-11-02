#include <iostream>
#include <cmath>
#include <vector>
#include "../interpolation.h"

double func(double x) {
    return 1.0 / (1.0 + x * x);
}

void work(int n) {
    std :: vector <double> x, f;
    for (int i = 0; i <= n; ++ i) {
        double xi = -5.0 + 10.0 * i / n;
        x.push_back(xi);
        f.push_back(func(xi));
    }
    Polynomial <double> p = newtonInterpolation(x, f);
    std :: cout << "When n = " << n  << ":" << std :: endl;
    p.print();
}

int main () {
    for (int i = 2; i <= 8; i += 2)
        work(i);
    return 0;
}