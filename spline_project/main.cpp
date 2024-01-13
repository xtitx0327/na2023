#include "xtspline.h"
#include "xtreader.h"

#include <vector>
#include <iostream>

enum SplineType {
    BSPLINE,
    PPSPLINE
};

int dim, order;
BoundaryCondition bc = BC_NONE;
double da = 0, db = 0;
SplineType sType;
std :: vector <std :: vector <double>> knots;

int main (int argc, char **argv) {
    try {
        freopen ("polynomials.txt", "w", stdout);
        XTReader reader (argv[1]);
        knots = reader.getData ("points");
        dim = reader.getData ("dimension");
        order = reader.getData ("order");
        if (reader.hasKey ("boundaryCondition")) {
            if (reader.getData ("boundaryCondition") == "CompleteCubic")
                bc = BC_COMPLETE_CUBIC;
            else if (reader.getData ("boundaryCondition") == "Natural")
                bc = BC_NATURAL;
            else if (reader.getData ("boundaryCondition") == "SecondDerivative")
                bc = BC_SECOND_DERIVATIVE;
            else
                throw "Invalid boundary condition";
        }
        if (reader.hasKey ("boundaryValues")) {
            std :: vector <double> boundary = reader.getData ("boundaryValues");
            if (boundary.size () != 2)
                throw "Invalid boundary values";
            da = boundary[0];
            db = boundary[1];
        }
        if (reader.getData ("splineType") == "BSpline")
            sType = BSPLINE;
        else if (reader.getData ("splineType") == "PPSpline")
            sType = PPSPLINE;
        else
            throw "Invalid spline type";
    } catch (const char *e) {
        std :: cerr << e << std :: endl;
    }
    if (sType == BSPLINE) {
        BSpline spline (dim, order, knots);
        spline.print ();
    } else {
        PPSpline spline (dim, order, knots, bc);
        spline.print ();
    }
    fclose (stdout);
    return 0;
}