#include "../../xtspline.h"
#include <cmath>

double f (double x) {
    return exp (x) - x * x + 2 * x * x * x;
}
Function func (*f);

int main () {
    freopen ("cubic_bspline.txt", "w", stdout);
    BSpline cubicSpline (1, 3, f, -1.0, 1.0, 16);
    cubicSpline.print ();
    fclose (stdout);
    freopen ("quad_bspline.txt", "w", stdout);
    BSpline quadSpline (1, 2, f, -1.0, 1.0, 16);
    quadSpline.print ();
    fclose (stdout);
    return 0;
}