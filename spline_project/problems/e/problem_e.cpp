#include "../../xtspline.h"
#include <cmath>
#include <vector>

double fx (double x) {
    return sqrt (3) * cos (x);
}

double fy (double x) {
    return 2.0 / 3.0 * (sqrt (sqrt (3) * fabs (cos (x))) + sqrt (3) * sin (x));
}

int main () {
    std :: vector <int> n = {10, 40, 160};
    for (int i = 0; i < n.size (); ++ i) {
        PPSpline splineX (1, 3, fx, -M_PI / 2, M_PI / 2, BC_NATURAL, n [i]);
        PPSpline splineY (1, 3, fy, -M_PI / 2, M_PI / 2, BC_NATURAL, n [i]);
        freopen (("x" + std :: to_string (n [i]) + ".txt").c_str (), "w", stdout);
        splineX.print ();
        fclose (stdout);
        freopen (("y" + std :: to_string (n [i]) + ".txt").c_str (), "w", stdout);
        splineY.print ();
        fclose (stdout);
    }
    return 0;
}