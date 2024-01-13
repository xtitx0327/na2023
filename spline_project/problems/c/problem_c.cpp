#include "../../xtspline.h"
#include <cmath>
#include <vector>

double f (double x) {
    return 1.0 / (1.0 + x * x);
}
Function func (*f);

inline double abs (double x) {
    return x > 0 ? x : (- x);
}

std :: vector <double> t1, t2;

int main () {
    // generate knots t1 & t2
    for (int i = 1; i <= 11; ++ i)
        t1.push_back (-6 + i);
    for (int i = 1; i <= 10; ++ i)
        t2.push_back ((double)i - 11.0 / 2.0);
    BSpline spline1 (1, 3, func, t1);
    BSpline spline2 (1, 2, func, t2);
    std :: vector <double> errList = {-3.5, -3, -0.5, 0, 0.5, 3, 3.5};
    for (int i = 0; i < errList.size (); ++ i) {
        double err1 = abs (spline1 (errList[i])[0] - f (errList[i]));
        double err2 = abs (spline2 (errList[i])[0] - f (errList[i]));
        std :: cerr << "Error at " << errList[i] << ":\n";
        std :: cerr << "Cubic spline: " << err1 << "\n";
        std :: cerr << "Quadratic spline: " << err2 << "\n";
    }
    freopen ("cubic.txt", "w", stdout);
    spline1.print ();
    fclose (stdout);
    freopen ("quad.txt", "w", stdout);
    spline2.print ();
    fclose (stdout);
    return 0;
}