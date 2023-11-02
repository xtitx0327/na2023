#include <vector>
#include <iostream>
#include "../interpolation.h"

int main() {
    std :: vector <double> times = {0, 3, 5, 8, 13};
    std :: vector <double> displacements = {0, 225, 383, 623, 993};
    std :: vector <double> velocities = {75, 77, 80, 74, 72};

    Polynomial <double> p = hermiteInterpolation(times, displacements, velocities);

    std :: cout << "Position at t = 10 seconds: " << p.evaluate(10.0) << " feet" << std :: endl;

    // Calculate the derivative of the polynomial to find the speed
    Polynomial <double> dp = p.derivative();
    std :: cout << "Speed at t = 10 seconds: " << dp.evaluate(10.0) << " feet/second" << std :: endl;

    // To determine if the car exceeds the speed limit, we'd have to find the maximum value of dp over the interval.
    // This would typically involve finding critical points (where dp's derivative is 0) and evaluating dp at those points,
    // but for simplicity, we'll just evaluate dp at the given times:
    bool exceedsLimit = false;
    for (double t : times)
        if (dp.evaluate(t) > 81.0) {
            exceedsLimit = true;
            break;
        }

    if (exceedsLimit) {
        std :: cout << "The car exceeds the speed limit of 81 feet/second." << std :: endl;
    } else {
        std :: cout << "The car does not exceed the speed limit of 81 feet/second." << std :: endl;
    }

    return 0;
}
