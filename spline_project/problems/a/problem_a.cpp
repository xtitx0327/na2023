#include "../../xtspline.h"
#include <vector>

inline double abs (double x) {
    return x > 0 ? x : (- x);
}

double f (double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

Function func (*f);

std :: vector <int> N = {6, 11, 21, 41, 81};

int main () {
    for (int i = 0; i < N.size (); ++ i) {
        freopen (("polynomials_" + std :: to_string (N [i]) + ".txt").c_str (), "w", stdout);
        PPSpline spline (1, 3, func, -1.0, 1.0, BC_COMPLETE_CUBIC, N [i]); // Build a complete cubic spline
        spline.print ();
        double maxError = 0.0;
        for (int j = 0; j < N [i] - 1; ++ j) {
            // Use midpoint of each interval as x
            double x = -1.0 + j * 2.0 / (N [i] - 1) + 1.0 / (N [i] - 1);
            double error = abs (spline (x)[0] - f (x));
            if (error > maxError)
                maxError = error;
        }
        std :: cerr << "Error for N = " << N [i] << ": " << maxError << std :: endl;
        fclose (stdout);
    }
    return 0;
}