#include <iostream>
#include <vector>
#include "../interpolation.h"

int main() {
    // Data points
    std :: vector <double> day = {0, 6, 10, 13, 17, 20, 28};
    std :: vector <double> sp1 = {6.67, 17.3, 42.7, 37.3, 30.1, 29.3, 28.7};
    std :: vector <double> sp2 = {6.67, 16.1, 18.9, 15.0, 10.6, 9.44, 8.89};

    // // Newton interpolation
    // Polynomial <double> sp1Poly = newtonInterpolation(day, sp1);
    // Polynomial <double> sp2Poly = newtonInterpolation(day, sp2);

    // // Evaluate at t = 43
    // double weightSp1_43 = sp1Poly.evaluate(43);
    // double weightSp2_43 = sp2Poly.evaluate(43);

    double weightSp1_43 = newtonInterpolation(day, sp1, 43.0);
    double weightSp2_43 = newtonInterpolation(day, sp2, 43.0);

    // Display the results
    std :: cout << "Predicted weight for Sp1 at 43 days: " << weightSp1_43 << " units" << std :: endl;
    std :: cout << "Predicted weight for Sp2 at 43 days: " << weightSp2_43 << " units" << std :: endl;

    if(weightSp1_43 <= 0) {
        std :: cout << "Sp1 larvae might die after 15 more days." << std :: endl;
    } else {
        std :: cout << "Sp1 larvae might survive after 15 more days." << std :: endl;
    }

    if(weightSp2_43 <= 0) {
        std :: cout << "Sp2 larvae might die after 15 more days." << std :: endl;
    } else {
        std :: cout << "Sp2 larvae might survive after 15 more days." << std :: endl;
    }

    return 0;
}
